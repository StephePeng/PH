/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2015, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     TDecSlice.cpp
    \brief    slice decoder class
*/

#include "TDecSlice.h"

//! \ingroup TLibDecoder
//! \{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TDecSlice::TDecSlice()
{
}

TDecSlice::~TDecSlice()
{
}

Void TDecSlice::create()
{
}

Void TDecSlice::destroy()
{
}

Void TDecSlice::init(TDecEntropy* pcEntropyDecoder, TDecCu* pcCuDecoder)
{
  m_pcEntropyDecoder  = pcEntropyDecoder;
  m_pcCuDecoder       = pcCuDecoder;
}

Void TDecSlice::decompressSlice(TComInputBitstream** ppcSubstreams, TComPic* pcPic, TDecSbac* pcSbacDecoder)
{
  TComSlice* pcSlice                 = pcPic->getSlice(pcPic->getCurrSliceIdx());

  const Int  startCtuTsAddr          = pcSlice->getSliceSegmentCurStartCtuTsAddr();
  const Int  startCtuRsAddr          = pcPic->getPicSym()->getCtuTsToRsAddrMap(startCtuTsAddr);
  const UInt numCtusInFrame          = pcPic->getNumberOfCtusInFrame();

  const UInt frameWidthInCtus        = pcPic->getPicSym()->getFrameWidthInCtus();
  const Bool depSliceSegmentsEnabled = pcSlice->getPPS()->getDependentSliceSegmentsEnabledFlag();
  const Bool wavefrontsEnabled       = pcSlice->getPPS()->getEntropyCodingSyncEnabledFlag();

  m_pcEntropyDecoder->setEntropyDecoder ( pcSbacDecoder  );
  m_pcEntropyDecoder->setBitstream      ( ppcSubstreams[0] );
  m_pcEntropyDecoder->resetEntropy      (pcSlice);

  // decoder doesn't need prediction & residual frame buffer
  pcPic->setPicYuvPred( 0 );
  pcPic->setPicYuvResi( 0 );

#if ENC_DEC_TRACE
  g_bJustDoIt = g_bEncDecTraceEnable;
#endif
  DTRACE_CABAC_VL( g_nSymbolCounter++ );
  DTRACE_CABAC_T( "\tPOC: " );
  DTRACE_CABAC_V( pcPic->getPOC() );
  DTRACE_CABAC_T( "\n" );

#if ENC_DEC_TRACE
  g_bJustDoIt = g_bEncDecTraceDisable;
#endif

  // The first CTU of the slice is the first coded substream, but the global substream number, as calculated by getSubstreamForCtuAddr may be higher.
  // This calculates the common offset for all substreams in this slice.
  const UInt subStreamOffset=pcPic->getSubstreamForCtuAddr(startCtuRsAddr, true, pcSlice);

  //PH
  //decrypt CtuSwap
  vector<TComDataCU*> CtuData;
  /*for (UInt ctuTsAddr = startCtuTsAddr; ctuTsAddr < numCtusInFrame; ++ctuTsAddr)
  {
	  const UInt ctuRsAddr = pcPic->getPicSym()->getCtuTsToRsAddrMap(ctuTsAddr);
	  TComDataCU* pCtu = pcPic->getCtu(ctuRsAddr);
	  pCtu->initCtu(pcPic, ctuRsAddr);
	  CtuData.push_back(pCtu);
  }
  if (pcSlice->getPOC() == 0&&pcSlice->getPOC()%8!=0)
  {
	  DecryptCtuSwap *decryptCtuSwap;
	  decryptCtuSwap = new DecryptCtuSwap();
	  vector<UInt> key;
	  key = decryptCtuSwap->readKeyFromFile(numCtusInFrame - frameWidthInCtus, pcSlice->getPOC());
	  CtuData = decryptCtuSwap->decryptCtuSwapMain(CtuData,key);
	  int debug;
  }*/
  //PH

  if (depSliceSegmentsEnabled)
  {
    // modify initial contexts with previous slice segment if this is a dependent slice.
    const UInt startTileIdx=pcPic->getPicSym()->getTileIdxMap(startCtuRsAddr);
    const TComTile *pCurrentTile=pcPic->getPicSym()->getTComTile(startTileIdx);
    const UInt firstCtuRsAddrOfTile = pCurrentTile->getFirstCtuRsAddr();

    if( pcSlice->getDependentSliceSegmentFlag() && startCtuRsAddr != firstCtuRsAddrOfTile)
    {
      if ( pCurrentTile->getTileWidthInCtus() >= 2 || !wavefrontsEnabled)
      {
        pcSbacDecoder->loadContexts(&m_lastSliceSegmentEndContextState);
      }
    }
  }

  // for every CTU in the slice segment...

  Bool isLastCtuOfSliceSegment = false;
  for( UInt ctuTsAddr = startCtuTsAddr; !isLastCtuOfSliceSegment && ctuTsAddr < numCtusInFrame; ctuTsAddr++)
  {
    const UInt ctuRsAddr = pcPic->getPicSym()->getCtuTsToRsAddrMap(ctuTsAddr);
    const TComTile &currentTile = *(pcPic->getPicSym()->getTComTile(pcPic->getPicSym()->getTileIdxMap(ctuRsAddr)));
    const UInt firstCtuRsAddrOfTile = currentTile.getFirstCtuRsAddr();
    const UInt tileXPosInCtus = firstCtuRsAddrOfTile % frameWidthInCtus;
    const UInt tileYPosInCtus = firstCtuRsAddrOfTile / frameWidthInCtus;
    const UInt ctuXPosInCtus  = ctuRsAddr % frameWidthInCtus;
    const UInt ctuYPosInCtus  = ctuRsAddr / frameWidthInCtus;
    const UInt uiSubStrm=pcPic->getSubstreamForCtuAddr(ctuRsAddr, true, pcSlice)-subStreamOffset;
	TComDataCU* pCtu = pcPic->getCtu(ctuRsAddr);;
    

	//TComDataCU* pCtu = CtuData[ctuRsAddr];
    pCtu->initCtu( pcPic, ctuRsAddr );

    m_pcEntropyDecoder->setBitstream( ppcSubstreams[uiSubStrm] );

    // set up CABAC contexts' state for this CTU
    if (ctuRsAddr == firstCtuRsAddrOfTile)
    {
      if (ctuTsAddr != startCtuTsAddr) // if it is the first CTU, then the entropy coder has already been reset
      {
        m_pcEntropyDecoder->resetEntropy(pcSlice);
      }
    }
    else if (ctuXPosInCtus == tileXPosInCtus && wavefrontsEnabled)
    {
      // Synchronize cabac probabilities with upper-right CTU if it's available and at the start of a line.
      if (ctuTsAddr != startCtuTsAddr) // if it is the first CTU, then the entropy coder has already been reset
      {
        m_pcEntropyDecoder->resetEntropy(pcSlice);
      }
      TComDataCU *pCtuUp = pCtu->getCtuAbove();
      if ( pCtuUp && ((ctuRsAddr%frameWidthInCtus+1) < frameWidthInCtus)  )
      {
        TComDataCU *pCtuTR = pcPic->getCtu( ctuRsAddr - frameWidthInCtus + 1 );
        if ( pCtu->CUIsFromSameSliceAndTile(pCtuTR) )
        {
          // Top-right is available, so use it.
          pcSbacDecoder->loadContexts( &m_entropyCodingSyncContextState );
        }
      }
    }

#if ENC_DEC_TRACE
    g_bJustDoIt = g_bEncDecTraceEnable;
#endif

	Int startByteIndex = m_pcEntropyDecoder->getEntropyDecoder()->getInputBitstream()->getByteLocation();
	Int startBitIndex = m_pcEntropyDecoder->getEntropyDecoder()->getTDecBinIf()->getBitsNeeded();
    if ( pcSlice->getSPS()->getUseSAO() )
    {
      SAOBlkParam& saoblkParam = (pcPic->getPicSym()->getSAOBlkParam())[ctuRsAddr];
      Bool bIsSAOSliceEnabled = false;
      Bool sliceEnabled[MAX_NUM_COMPONENT];
      for(Int comp=0; comp < MAX_NUM_COMPONENT; comp++)
      {
        ComponentID compId=ComponentID(comp);
        sliceEnabled[compId] = pcSlice->getSaoEnabledFlag(toChannelType(compId)) && (comp < pcPic->getNumberValidComponents());
        if (sliceEnabled[compId])
        {
          bIsSAOSliceEnabled=true;
        }
        saoblkParam[compId].modeIdc = SAO_MODE_OFF;
      }
      if (bIsSAOSliceEnabled)
      {
        Bool leftMergeAvail = false;
        Bool aboveMergeAvail= false;

        //merge left condition
        Int rx = (ctuRsAddr % frameWidthInCtus);
        if(rx > 0)
        {
          leftMergeAvail = pcPic->getSAOMergeAvailability(ctuRsAddr, ctuRsAddr-1);
        }
        //merge up condition
        Int ry = (ctuRsAddr / frameWidthInCtus);
        if(ry > 0)
        {
          aboveMergeAvail = pcPic->getSAOMergeAvailability(ctuRsAddr, ctuRsAddr-frameWidthInCtus);
        }

        pcSbacDecoder->parseSAOBlkParam( saoblkParam, sliceEnabled, leftMergeAvail, aboveMergeAvail, pcSlice->getSPS()->getBitDepths());
      }
    }

	if (ctuRsAddr == 65&&false)
	{
		for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		{
			if (i % 16 == 0)
				printf("\n");
			printf("%d ", pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i));

		}
		printf("\n\n");
		for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		{
			if (i % 16 == 0)
				printf("\n");
			printf("(%d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getHor());
		}
		printf("\n\n");
		for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		{
			if (i % 16 == 0)
				printf("\n");
			printf("(%d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i).getHor());
		}
		printf("\n");
		int debug = 0;
	}
    m_pcCuDecoder->decodeCtu     ( pCtu, isLastCtuOfSliceSegment );
	if (ctuRsAddr == 65&&false)
	{
		for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		{
			if (i % 16 == 0)
				printf("\n");
			printf("%d ", pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i));

		}
		printf("\n\n");
		for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		{
			if (i % 16 == 0)
				printf("\n");
			printf("(%d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getHor());
		}
		printf("\n\n");
		for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		{
			if (i % 16 == 0)
				printf("\n");
			printf("(%d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i).getHor());
		}
		printf("\n");
		int debug = 0;
	}

	
	
	CtuData.push_back(pCtu);
    //m_pcCuDecoder->decompressCtu ( pCtu );
	/*if (pcSlice->getPOC() == 3 && ctuRsAddr == 65)
	{
		for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		{
			if (i % 16 == 0)
				printf("\n");
			printf("(%d, %d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getHor(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i));
		}
		printf("\n");
	}*/

	Int endByteIndex = m_pcEntropyDecoder->getEntropyDecoder()->getInputBitstream()->getByteLocation();
	Int endBitIndex = m_pcEntropyDecoder->getEntropyDecoder()->getTDecBinIf()->getBitsNeeded();
	int numBits = (endByteIndex - startByteIndex) * 8 + endBitIndex - startBitIndex;
	if (pcSlice->getPOC()>0)
	{
		writeCtuNumBits(numBits, pcSlice->getPOC());
	}

#if ENC_DEC_TRACE
    g_bJustDoIt = g_bEncDecTraceDisable;
#endif

    //Store probabilities of second CTU in line into buffer
    if ( ctuXPosInCtus == tileXPosInCtus+1 && wavefrontsEnabled)
    {
      m_entropyCodingSyncContextState.loadContexts( pcSbacDecoder );
    }

    if (isLastCtuOfSliceSegment)
    {
#if DECODER_CHECK_SUBSTREAM_AND_SLICE_TRAILING_BYTES
      pcSbacDecoder->parseRemainingBytes(false);
#endif
      if(!pcSlice->getDependentSliceSegmentFlag())
      {
        pcSlice->setSliceCurEndCtuTsAddr( ctuTsAddr+1 );
      }
      pcSlice->setSliceSegmentCurEndCtuTsAddr( ctuTsAddr+1 );
    }
    else if (  ctuXPosInCtus + 1 == tileXPosInCtus + currentTile.getTileWidthInCtus() &&
             ( ctuYPosInCtus + 1 == tileYPosInCtus + currentTile.getTileHeightInCtus() || wavefrontsEnabled)
            )
    {
      // The sub-stream/stream should be terminated after this CTU.
      // (end of slice-segment, end of tile, end of wavefront-CTU-row)
      UInt binVal;
      pcSbacDecoder->parseTerminatingBit( binVal );
      assert( binVal );
#if DECODER_CHECK_SUBSTREAM_AND_SLICE_TRAILING_BYTES
      pcSbacDecoder->parseRemainingBytes(true);
#endif
    }

  }
  
  //PH

  if ((pcSlice->getPOC()==0)&&false)
  {
	  DecryptCtuSwap *decryptCtuSwap;
	  decryptCtuSwap = new DecryptCtuSwap();
	  vector<UInt> key;
	  key = decryptCtuSwap->readKeyFromFile(numCtusInFrame - frameWidthInCtus, pcSlice->getPOC());
	  CtuData = decryptCtuSwap->decryptCtuSwapMain(CtuData, key);

	  for (int i = 0; i < CtuData.size(); i++)
	  {
		  pcPic->getPicSym()->setCtu(i, CtuData[i]);
	  }
	  int debug;
  }
 /* for (int i = 0; i < numCtusInFrame; i++)
  {
	  if (i%frameWidthInCtus == 0)
		  printf("\n");
	  printf("%d ", CtuData[i]->getCtuRsAddr());
  }
  printf("\n");
  for (int i = 0; i < numCtusInFrame; i++)
  {
	  printf("%d: ", i);
	  if (CtuData[i]->getCtuLeft() != NULL)printf("Left: %d ", CtuData[i]->getCtuLeft()->getCtuRsAddr());
	  if (CtuData[i]->getCtuAbove() != NULL)printf("Above %d ", CtuData[i]->getCtuAbove()->getCtuRsAddr());
	  if (CtuData[i]->getCtuAboveLeft() != NULL)printf("AboveLeft %d ", CtuData[i]->getCtuAboveLeft()->getCtuRsAddr());
	  if (CtuData[i]->getCtuAboveRight() != NULL)printf("AboveRight %d ", CtuData[i]->getCtuAboveRight()->getCtuRsAddr());
	  printf("\n");
  }*/
  /*for (int i = 0; i < numCtusInFrame; i++)
  {
	  if (i%frameWidthInCtus == 0)
		  printf("\n");
	  printf("(%d,%d) ", CtuData[i]->getCUPelX(), CtuData[i]->getCUPelY());
  }
  printf("\n");*/
  /*for (int i = 0; i < numCtusInFrame; i++)
  {
	  if (i%frameWidthInCtus == 0)printf("\n");
	  if (CtuData[i]->getCUColocated(REF_PIC_LIST_0) != NULL)
		  printf("%d ",CtuData[i]->getCUColocated(REF_PIC_LIST_0)->getCtuRsAddr());
  }*/
 
  isLastCtuOfSliceSegment = false;
  for (UInt ctuTsAddr = startCtuTsAddr; !isLastCtuOfSliceSegment && ctuTsAddr < numCtusInFrame; ctuTsAddr++)
  {
	  const UInt ctuRsAddr = pcPic->getPicSym()->getCtuTsToRsAddrMap(ctuTsAddr);
	  TComDataCU* pCtu = CtuData[ctuRsAddr];
	  /*if (pcSlice->getPOC() == 6 && ctuRsAddr == 5)
	  {
		  for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		  {
			  if (i % 16 == 0)
				  printf("\n");
			  printf("(%d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getHor());
		  }
		  printf("\n");
		  int debug = 0;
	  }*/
	 /* if (pcSlice->getPOC() == 3 && ctuRsAddr == 4)
	  {
		  for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		  {
			  if (i % 16 == 0)
				  printf("\n");
			  printf("(%d, %d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getHor(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i));
		  }
		  printf("\n");
		  int debug = 0;
	  }*/
	  m_pcCuDecoder->resetCtuMv(pCtu, isLastCtuOfSliceSegment);
	  /*if (pcSlice->getPOC() == 6 && ctuRsAddr == 5)
	  {
	  for (int i = 0; i < pCtu->getTotalNumPart(); i++)
	  {
	     if (i % 16 == 0)
	        printf("\n");
	      printf("(%d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getHor());
	  }
	      printf("\n");
		  int debug = 0;
	  }*/
	  /*if (pcSlice->getPOC() == 3 && ctuRsAddr == 4)
	  {
		  for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		  {
			  if (i % 16 == 0)
				  printf("\n");
			  printf("(%d, %d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getHor(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i));
		  }
		  printf("\n");
		  int debug = 0;
	  }*/
	  if (ctuRsAddr == 4&&false)
	  {
		  for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		  {
			  if (i % 16 == 0)
				  printf("\n");
			  printf("%d ", pCtu->getCUMvField(REF_PIC_LIST_0)->getRefIdx(i));

		  }
		  printf("\n\n");
		  for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		  {
			  if (i % 16 == 0)
				  printf("\n");
			  printf("(%d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMv(i).getHor());
		  }
		  printf("\n\n");
		  for (int i = 0; i < pCtu->getTotalNumPart(); i++)
		  {
			  if (i % 16 == 0)
				  printf("\n");
			  printf("(%d, %d)", pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i).getVer(), pCtu->getCUMvField(REF_PIC_LIST_0)->getMvd(i).getHor());
		  }
		  printf("\n");
		  int debug = 0;
	  }
	  m_pcCuDecoder->decompressCtu(pCtu);
  }
  isLastCtuOfSliceSegment = true;
  //PH

  assert(isLastCtuOfSliceSegment == true);


  if( depSliceSegmentsEnabled )
  {
    m_lastSliceSegmentEndContextState.loadContexts( pcSbacDecoder );//ctx end of dep.slice
  }

}

//! \}
Void TDecSlice::writeCtuNumBits(Int numBits, Int picNum)
{
	int group;
	if (picNum % 2 != 0)
		group = 1;
	else if (picNum % 2 == 0 && picNum % 4 != 0)
		group = 2;
	else
		group = 3;
	fstream f;
	switch (group)
	{
	case 1:
		f.open("data1.txt", ios::app);
		f << numBits << " ";
		break;
	case 2:
		f.open("data2.txt", ios::app);
		f << numBits << " ";
		break;
	case 3:
		f.open("data3.txt", ios::app);
		f << numBits << " ";
		break;
	default:
		break;
	}
	f.close();
}