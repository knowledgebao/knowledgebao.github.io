
#include "chapter.h"
#include "Other.h"
#include "opencv.h"

void testOpencv_h() {
	unsigned char I420[24] = {
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1,//Y
		3, 3, 3, 3,//U
		2, 2, 2, 2 };//V
	
	char* p = (char*)I420;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			printf("%d ", p[i * 8 + j]);
		}
		printf("\n");
	}  

	unsigned char NV12[24*4];//4*4
	ImageInfo canvas{};
	canvas.data = (uintptr_t)NV12;
	canvas.scale = NV12ScaleCV;
	canvas.width = 8;
	canvas.height = 8;
	ImageInfo img{};
	img.data = (uintptr_t)I420;
	img.scale = I420ScaleCV;
	img.width = 4;
	img.height = 4;
	ImageRect rect{0,0,4,4};
	NV12Draw(canvas, img, rect, false);
	p = (char*)canvas.data;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%d ", p[i * 8 + j]);
		}
		printf("/n");
	}
}

int main(int argc, char** argv)
{
	//testOpencv_h();
	mytest(argc, argv);
	//TestResize(argc, argv);
	// read image
	//chapter001(argc, argv);
	//chapter002(argc, argv);
	//chapter003(argc, argv);
	//chapter004(argc, argv);
	//chapter005(argc, argv);
	//chapter006(argc, argv);
	//chapter007(argc, argv);
	//chapter008(argc, argv);
	//chapter009(argc, argv);
	//chapter010(argc, argv);
	//chapter011(argc, argv);
	//chapter012(argc, argv);
	//chapter013(argc, argv);
	//chapter014(argc, argv);
	//chapter015(argc, argv);
	//chapter016::chapter016(argc, argv);
	//chapter017(argc, argv);
	//chapter018(argc, argv);
	//chapter019(argc, argv);
	//chapter020(argc, argv);
	//chapter021::chapter021(argc, argv);
	//chapter022(argc, argv);
	//chapter023(argc, argv);
	//chapter024::chapter024(argc, argv);
	//chapter025(argc, argv);
	//chapter026(argc, argv);
	//chapter027(argc, argv);
	//chapter028::chapter028(argc, argv);
	//chapter029::chapter029(argc, argv);
	//chapter030::chapter030(argc, argv);
	//chapter031::chapter031(argc, argv);
	//chapter032::chapter032(argc, argv);
	//chapter033::chapter033(argc, argv);
	//chapter034(argc, argv);
	//chapter035(argc, argv);
	return 0;
}