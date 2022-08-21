#include <stdint.h>

// X68KのCGROMを作る
// buf:           作る領域 (0xc0000バイト分のバッファ)
// x68030:        X68030フォントを作るか？ (現在無効)
// primaryface:   書体１ (主に16ドット用)
// secondaryface: 書体２ (主に24ドット用)
//
// 戻り値:         FALSE: 失敗, TRUE: 成功

/*
 * WIN32 structure
 */
typedef struct {
	uint16_t	bfType;
	uint32_t	bfSize;
	uint16_t	bfReserved1;
	uint16_t	bfReserved2;
	uint32_t	bfOffBits;
} __attribute__ ((packed)) BITMAPFILEHEADER;

typedef struct {
	uint32_t	biSize;
//	int32_t	biWidth;
//	int32_t	biHeight;
	uint16_t	biPlanes;
	uint16_t	biBitCount;
	uint32_t	biCompression;
	uint32_t	biSizeImage;
//	int32_t	biXPelsPerMeter;
//	int32_t	biYPelsPerMeter;
	uint32_t	biClrUsed;
	uint32_t	biClrImportant;
} __attribute__ ((packed)) BITMAPINFOHEADER;

typedef struct {
	uint8_t	rgbBlue;
	uint8_t	rgbGreen;
	uint8_t	rgbRed;
	uint8_t	rgbReserved;
} __attribute__ ((packed)) RGBQUAD;

typedef struct {
	BITMAPINFOHEADER	bmiHeader;
	RGBQUAD			bmiColors[1];
} __attribute__ ((packed)) BITMAPINFO;

typedef struct {
	uint32_t	top;
	uint32_t	left;
	uint32_t	bottom;
	uint32_t	right;
} RECT;

int make_cgromdat(uint8_t *buf, int x68030, LPSTR primaryface, LPSTR secondaryface);
