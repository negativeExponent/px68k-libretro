
// X68K��CGROM����
// buf:           ����ΰ� (0xc0000�Х���ʬ�ΥХåե�)
// x68030:        X68030�ե���Ȥ��뤫�� (����̵��)
// primaryface:   ���Σ� (���16�ɥå���)
// secondaryface: ���Σ� (���24�ɥå���)
//
// �����:         FALSE: ����, TRUE: ����

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
	long	biWidth;
	long	biHeight;
	uint16_t	biPlanes;
	uint16_t	biBitCount;
	uint32_t	biCompression;
	uint32_t	biSizeImage;
	long	biXPelsPerMeter;
	long	biYPelsPerMeter;
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


int make_cgromdat(BYTE *buf, int x68030, LPSTR primaryface, LPSTR secondaryface);
