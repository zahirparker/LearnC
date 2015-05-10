#include<stdio.h>
#include "typedefs.h"


// Method 1 : 32 bits defined as bitfields
typedef union
{
    struct
    {
        UINT32 b8_ParamValue        : 8;    /*  bits  7:  0  */
        UINT32 b8_CollectSamples    : 8;    /*  bits 15:  8  */
        UINT32 b7_SkipSamples       : 7;    /*  bits 22: 16  */
        UINT32 b1_ChirpBreak        : 1;    /*  bits 23: 23  */
        UINT32 b8_Reserved          : 8;    /*  bits 31: 24  */
    } bytes;
    UINT32 b32_Val;
} U_GPADC_PARAM_SAMPLE_INFO;

// Method 1 : 32 bits defined as 4 bytes
typedef union
{
    struct
    {
        UINT8 b8_ParamValue        ;    /*  bits  7:  0  */
        UINT8 b8_CollectSamples    ;    /*  bits 15:  8  */
        UINT8 b8_SkipSamples       ;    /*  bits 23: 16  */
        UINT8 b8_Reserved          ;    /*  bits 31: 24  */
    } bytes;
    UINT32 b32_Val;
} U_GPADC_PARAM_SAMPLE_INFO_B;

typedef struct
{
	UINT32 ConfigValue;
  U_GPADC_PARAM_SAMPLE_INFO ParamInfo;
  UINT16 MinThr;
  UINT16 MaxThr;
} U_GPADC_BIST_PARAM;


typedef struct
{
	UINT32 ConfigValue;
  U_GPADC_PARAM_SAMPLE_INFO_B ParamInfo;
  UINT16 MinThr;
  UINT16 MaxThr;
} U_GPADC_BIST_PARAM_B;


#define M_GPADC_MAX_PARAMS 100U

// Method 1: Have to declare 5 bitfields just the way it is declared in the union
U_GPADC_BIST_PARAM BistParams[M_GPADC_MAX_PARAMS] = {
  //ConfigValue, { ParamValue, CollectSamples, SkipSamples, ChirpBreak, Reserved}, MinThr, MaxThr
  {0x1, {0x12, 0x34, 0x76, 0x1, 0x0 }, 0x100, 0x200},    //Note that 0xf6 is taken as 0x76 because it is defined as 7 bit field
  {0x1, {0x12, 0x34, 0x76, 0x0, 0x0 }, 0x100, 0x200},
};

// Method 1: Have to declare 4 fields bytewise just the way it is declared in the union
U_GPADC_BIST_PARAM_B BistParams_b[M_GPADC_MAX_PARAMS] = {
  //ConfigValue, { ParamValue, CollectSamples, SkipSamples}, MinThr, MaxThr
  {0x1, {0x12, 0x34, 0x56, 0x78 }, 0x100, 0x200}
};




void endian(void)
{
   unsigned int i = 1;
   char *c = (char*)&i;
   if (*c)
       printf("Little endian\n");
   else
       printf("Big endian\n");
}



main()
{
    endian();

    // Method 1: uses one base pointer for the 32 bit field and does a read
    // modify write

    printf ("Addr ConfigValue     %p \n", &BistParams[0].ConfigValue);
    printf ("Addr ParamInfo       %p \n", &BistParams[0].ParamInfo);
    printf ("Addr ParamValue      %p \n", &BistParams[0].ParamInfo.bytes.b8_ParamValue);
    printf ("Addr CollectSamples  %p \n", &BistParams[0].ParamInfo.bytes.b8_CollectSamples);
    printf ("Addr SkipSamples     %p \n", &BistParams[0].ParamInfo.bytes.b7_SkipSamples);
    printf ("Addr ChirpBreak      %p \n", &BistParams[0].ParamInfo.bytes.b1_ChirpBreak);
    printf ("Addr Reserved        %p \n", &BistParams[0].ParamInfo.bytes.b8_Reserved);
    printf ("Addr MinThr          %p \n", &BistParams[0].MinThr);
    printf ("Addr MaxThr          %p \n", &BistParams[0].MaxThr);

    printf ("ConfigValue     : 0x%x \n", BistParams[0].ConfigValue);
    printf ("ParamInfo       : 0x%x \n", BistParams[0].ParamInfo.b32_Val);
    printf ("ParamValue      : 0x%x \n", BistParams[0].ParamInfo.bytes.b8_ParamValue);
    printf ("CollectSamples  : 0x%x \n", BistParams[0].ParamInfo.bytes.b8_CollectSamples);
    printf ("SkipSamples     : 0x%x \n", BistParams[0].ParamInfo.bytes.b7_SkipSamples);
    printf ("ChirpBreak      : 0x%x \n", BistParams[0].ParamInfo.bytes.b1_ChirpBreak);
    printf ("Reserved        : 0x%x \n", BistParams[0].ParamInfo.bytes.b8_Reserved);
    printf ("MinThr          : 0x%x \n", BistParams[0].MinThr);
    printf ("MaxThr          : 0x%x \n", BistParams[0].MaxThr);

    //printf ("BistParams                %d \n", sizeof(BistParams));
    //printf ("BistParams[0]             %d \n", sizeof(BistParams[0]));
    //printf ("BistParams[0].ConfigValue %d \n", sizeof(BistParams[0].ConfigValue));
    //printf ("BistParams[0].ParamInfo   %d \n", sizeof(BistParams[0].ParamInfo));
    //printf ("%d \n", sizeof(U_GPADC_PARAM_SAMPLE_INFO));
    //
    printf ("\n\n");


    // Method 1: has different address for each byte, takes the advantage of
    // byte enabled while writing/reading
    printf ("Addr ConfigValue     %p \n", &BistParams_b[0].ConfigValue);
    printf ("Addr ParamInfo       %p \n", &BistParams_b[0].ParamInfo);
    printf ("Addr ParamValue      %p \n", &BistParams_b[0].ParamInfo.bytes.b8_ParamValue);
    printf ("Addr CollectSamples  %p \n", &BistParams_b[0].ParamInfo.bytes.b8_CollectSamples);
    printf ("Addr SkipSamples     %p \n", &BistParams_b[0].ParamInfo.bytes.b8_SkipSamples);
    //printf ("Addr ChirpBreak      %p \n", &BistParams_b[0].ParamInfo.bytes.b1_ChirpBreak);
    printf ("Addr Reserved        %p \n", &BistParams_b[0].ParamInfo.bytes.b8_Reserved);
    printf ("Addr MinThr          %p \n", &BistParams_b[0].MinThr);
    printf ("Addr MaxThr          %p \n", &BistParams_b[0].MaxThr);

    printf ("ConfigValue     : 0x%x \n", BistParams_b[0].ConfigValue);
    printf ("ParamInfo       : 0x%x \n", BistParams_b[0].ParamInfo.b32_Val);
    printf ("ParamValue      : 0x%x \n", BistParams_b[0].ParamInfo.bytes.b8_ParamValue);
    printf ("CollectSamples  : 0x%x \n", BistParams_b[0].ParamInfo.bytes.b8_CollectSamples);
    printf ("SkipSamples     : 0x%x \n", BistParams_b[0].ParamInfo.bytes.b8_SkipSamples);
    //printf ("ChirpBreak      : 0x%x \n", BistParams_b[0].ParamInfo.bytes.b1_ChirpBreak);
    printf ("Reserved        : 0x%x \n", BistParams_b[0].ParamInfo.bytes.b8_Reserved);
    printf ("MinThr          : 0x%x \n", BistParams_b[0].MinThr);
    printf ("MaxThr          : 0x%x \n", BistParams_b[0].MaxThr);

    //printf ("BistParams_b                %d \n", sizeof(BistParams_b));
    //printf ("BistParams_b[0]             %d \n", sizeof(BistParams_b[0]));
    //printf ("BistParams_b[0].ConfigValue %d \n", sizeof(BistParams_b[0].ConfigValue));
    //printf ("BistParams_b[0].ParamInfo   %d \n", sizeof(BistParams_b[0].ParamInfo));
    //printf ("%d \n", sizeof(U_GPADC_PARAM_SAMPLE_INFO));
    exit(1);
}


