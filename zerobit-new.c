#if 1
#include <stdio.h>
#include <stdint.h>
#include <time.h>

typedef struct result{
  uint8_t _16bitcnt;
  uint8_t remainder1;
  uint8_t remainder2; 
}result_t;

uint32_t addZeroBit(uint8_t *inBuff, uint16_t size, uint8_t *outBuff);  
uint32_t printOutput(uint8_t *arr, uint16_t size);
int main()
{
  srand(time(NULL));
  result_t results;
  uint8_t input[56] = {0};
  for(int i =0; i < sizeof(input); i++ ){
    input[i] = (i);
  }
  

  uint8_t output[sizeof(input)] = {0};
  uint32_t newLen = addZeroBit(input,sizeof(input), output);
  printf("New bit length : %d\n",newLen);
  printOutput(output, newLen / 8 +1);

  calculateBuffers(newLen, &results);
  return 0;
}


uint32_t addZeroBit(uint8_t *inBuff, uint16_t size, uint8_t *outBuff)
{
  uint16_t inBitIndex = 0, outBitIndex = 0;
  uint32_t firstSize = 0, addedZeros = 0;
  uint32_t consecituveFive = 0;

  while(firstSize < size *8){
    
    uint8_t inBit = (inBuff[inBitIndex / 8] >> (inBitIndex % 8) ) & 0x1;

    if(inBit){
      outBuff[outBitIndex /8] |= 0x1 << (outBitIndex % 8);
    }
    else{
      outBuff[outBitIndex /8] &= ~(0x1 << (outBitIndex % 8) );
    }

    uint8_t outBit = (outBuff[outBitIndex /8] >> (outBitIndex % 8) ) & 0x1;
    if(outBit){
      consecituveFive ++;
    }
    else{
      consecituveFive = 0;
    }

    /* Increment inbit and outbit indexes*/
    inBitIndex ++;
    outBitIndex ++;

    if(consecituveFive == 5){
      outBuff[outBitIndex /8] &= ~(0x1 << ( (outBitIndex++) % 8) );
      addedZeros ++;

      /* Newly added bugfix for consecutive five exceeding 5*/
      consecituveFive = 0;
    }

    firstSize ++;
  }
  return firstSize + addedZeros;
}

uint32_t printOutput(uint8_t *arr, uint16_t size)
{
  for(int i = 0; i < size; i++){
    printf("0x%x ", *(arr +i ) );
  }
}

void calculateBuffers(uint16_t len, result_t *result)
{
  if(len % 16 == 1){
    result->_16bitcnt = len / 16 -1;
    result->remainder1 = 15;
    result->remainder2 = 2;
  }
  else{
    result->_16bitcnt = len / 16;
    len -= (len / 16) * 16;
    result->remainder1 = len ;
  }
  
}

#endif