#if 0

#include <stdio.h>
#include <stdint.h>


#define calculateByteOffset(x) x / 8

uint32_t addZeroBit(uint8_t *inBuff, uint16_t size, uint8_t *outBuff);  
uint32_t printOutput(uint8_t *arr, uint16_t size);
int main()
{
  uint8_t input[3] = {0xda, 0xff, 0x1f};
  uint8_t output[4] = {0};
  uint32_t newLen = addZeroBit(input,sizeof(input), output);
  printf("New bit length : %d\n",newLen);
  printOutput(output, newLen / 8 +1);
  return 0;
}


uint32_t addZeroBit(uint8_t *inBuff, uint16_t size, uint8_t *outBuff)
{
  uint16_t inBitIndex = 0, outBitIndex = 0;
  uint16_t inByteIndex = 0, outByteIndex = 0;
  uint32_t firstSize = 0, addedZeros = 0;
  uint32_t consecituveFive = 0;

  while(firstSize < size *8){
    
    uint8_t inBit = (inBuff[inByteIndex] >> (inBitIndex % 8) ) & 0x1;

    if(inBit){
      outBuff[outByteIndex] |= 0x1 << (outBitIndex % 8);
    }
    else{
      outBuff[outByteIndex] &= ~(0x1 << (outBitIndex % 8) );
    }

    uint8_t outBit = (outBuff[outByteIndex] >> (outBitIndex % 8) ) & 0x1;
    if(outBit){
      consecituveFive ++;
    }
    else{
      consecituveFive = 0;
    }

    /* Increment inbit and outbit indexes*/
    inBitIndex ++;
    outBitIndex ++;

    /* calculate new byte offsets*/
    inByteIndex = calculateByteOffset(inBitIndex);
    outByteIndex = calculateByteOffset(outBitIndex);

    if(consecituveFive == 5){
      outBuff[outByteIndex] &= ~(0x1 << ( (outBitIndex++) % 8) );
      addedZeros ++;

      /* Newly added bugfix for consecutive five exceeding 5*/
      consecituveFive = 0;
    }

    /* Newly added bugfix for overriding previous byte */
    inByteIndex = calculateByteOffset(inBitIndex);
    outByteIndex = calculateByteOffset(outBitIndex);

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

#endif