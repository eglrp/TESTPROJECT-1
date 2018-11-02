
#include"CustomScroll.h"
#include <QtGui>
#include"iostream"
#include"imageviewer.h"
CustomScroll::CustomScroll(  )
{
    scrollArea = this;

    imageLabel  = new DrawLabel();
    imageLabel->setBackgroundRole(QPalette::Dark);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setWidget(imageLabel);
    image = imageLabel->image;
    imageLabel->FatherScroll = this;

    for(int i = 0; i< 256; i++)
    {
      //  QRgb cl(i,i,i);
        QRgb cl = qRgb(i,i,i);
       // ByteMapColorTable.append(i);
        ByteMapColorTable.append(cl);
    }
    setMouseTracking(true);

    this->viewport()->setMouseTracking(true);

    scaleFactor =1;
    MouseDown = false;
    MouseLeftButtonDown = false;
    CurrentToolType = Tool_pan;
    poDataset = NULL;
    ScopeChangedByClickScrollBar = true;

    FeatPtDataSet = NULL;

    connect(imageLabel,SIGNAL(mouseMoveSignal(int,int)),this,SLOT(DrawLabelMouseMoveSlot(int,int)));
    ActDeleteSelectedPts = new QAction(tr("Delete Selected Pts"),this);
    connect(ActDeleteSelectedPts,SIGNAL(triggered()),this,SLOT(DeleteSelectedFeatPt()));

    PickedAPoint= false;
}
/* ����scrollarea�Ĵ�Сȷ�������Ĵ�С��ͼƬ�Ĵ�С�Լ�ͼƬ���Ͻ��ڻ����е�λ��
  ����1�� ����դ�������ڻ����еľ���
  ����2�� ���ű���
  ����3�� �����������Ҫ���Ƶ�ͼƬ�Ŀ��
  ����4�� �����������Ҫ���Ƶ�ͼƬ�ĸ߶�
  ����5�� �����������Ҫ���Ƶ�ͼƬ���Ͻ���դ�������е�����
  ����6�� �����������Ҫ���Ƶ�ͼƬ���Ͻ��ڻ����е�λ�ã������½ǿ���ͨ��ͼƬ�Ŀ�Ⱥ͸߶�ȷ��
  ����7�� �����������Ҫ���Ƶ�ͼƬ�����½���դ�������е�λ��
*/
bool CustomScroll::ComputeImageSizeAndLocation(_mlRECT RasterSourceRect,
                                              double Scale,
                                              double &ImageWidth,
                                              double &ImageHeight ,
                                              _mlPOINT &LeftTopInRaster,
                                              _mlPOINT &LeftTopInCanvas ,
                                              _mlPOINT &RightBottomInRaster)
{
    try
    {
        QRect qs =  scrollArea->geometry();
        int canvasheight =qs.height();
        int canvaswidth = qs.width();
        // location in canvas
        if(RasterSourceRect.left <0)
        {
            LeftTopInCanvas.x = 0;
        }
        else
        {
            LeftTopInCanvas.x = RasterSourceRect.left;
        }
        if(RasterSourceRect.top <0)
        {
            LeftTopInCanvas.y = 0;
        }
        else
        {
            LeftTopInCanvas.y= RasterSourceRect.top;
        }
        // imagesize
        if(RasterSourceRect.bottom> canvasheight)
        {
            ImageHeight = canvasheight - LeftTopInCanvas.y;
        }
        else
        {
            ImageHeight = RasterSourceRect.bottom - LeftTopInCanvas.y;
        }
        if(RasterSourceRect.right >canvaswidth)
        {
            ImageWidth = canvaswidth - LeftTopInCanvas.x;
        }
        else
        {
            ImageWidth = RasterSourceRect.right - LeftTopInCanvas.x;
        }
        if(ImageHeight < 0 || ImageWidth < 0)
        {
            ImageHeight = ImageWidth = 0;
        }
    //imgxsize Ϊ����ʱ����ȡ��ͼƬ��Ť�������Ҫ����

    //���ǵ���DrawPicture �����е�int nLineSpace ��������Ϊ,
    //y��������������֮����ֽ�ƫ��, Ĭ��Ϊ0,���м��ʵ���ֽ�ƫ��ΪeBufType * nBufXSize,�ò�������Ҫ��4�ı���ͼ��Ų���Ť��,
    //��eBufType Ϊ1���ֽ�ʱ���� nBufXSize ����Ϊ4�ı�������
        if((int)ImageWidth %4 != 0)
        {
            ImageWidth += 4 - (int)ImageWidth %4 ;
        }
        // location in raster
        if(LeftTopInCanvas.x > 0)
        {
            LeftTopInRaster.x =0;
        }
        else
        {
            LeftTopInRaster.x =(0.0 - RasterSourceRect.left) * Scale;
        }
        if(LeftTopInCanvas.y > 0)
        {
            LeftTopInRaster.y = 0;
        }
        else
        {
            LeftTopInRaster.y =(0.0 - RasterSourceRect.top) * Scale;
        }
        RightBottomInRaster.x =  ImageWidth * Scale + LeftTopInRaster.x;
        if(RightBottomInRaster.x > RasterWidth)
        {
            RightBottomInRaster.x = RasterWidth;
        }
        if( RightBottomInRaster.x==0)
        {
            RightBottomInRaster.x=1;
        }
        RightBottomInRaster.y = ImageHeight * Scale + LeftTopInRaster.y;
        if(RightBottomInRaster.y  > RasterHeight)
        {
            RightBottomInRaster.y  = RasterHeight;
        }
        if( RightBottomInRaster.y==0)
        {
            RightBottomInRaster.y=1;
        }
        //��ͼƬ�Ŵ�ܶ౶ʱ��Ϊ��ʹ������ʾ�����������仯����Ҫ������ȡ��
        if(Scale < 1)
        {

            /*
            // ����С���������,������λ��ȡ����
            if(RightBottomInRaster.x > (int)RightBottomInRaster.x)
            {
                int a = (int)RightBottomInRaster.x ;
                RightBottomInRaster.x = a + 1;
                ImageWidth = ImageWidth * RightBottomInRaster.x / a;
            }
            if(RightBottomInRaster.y > (int)RightBottomInRaster.y)
            {
                int a = (int)RightBottomInRaster.y;
                RightBottomInRaster.y = a + 1;
                ImageHeight = ImageHeight * RightBottomInRaster.y / a;
            }
            */

        }
        return true;
    }
    catch(...)
    {
        return false;
    }
}
/* �������ű����Լ� դ���������Ͻ��ڻ����е������������դ�������ڻ����еľ���

  ����1�� �������������դ�������ڻ����еľ���
  ����2�� ���ű���
  ����3�� դ�����Ͻ��ڻ����е�����
  */
 bool CustomScroll::ComputeRasterRect(_mlRECT &rasterRect,double Scale ,_mlPOINT topleftincanvas)
 {
     try
     {
         rasterRect.left=topleftincanvas.x;
         rasterRect.top= topleftincanvas.y;
         rasterRect.right = topleftincanvas.x + (1.0 *RasterWidth )/ Scale;
         rasterRect.bottom = topleftincanvas.y + (1.0 * RasterHeight) / Scale;
         return true;
     }
     catch(...)
     {
         return false;
     }
 }

 void CustomScroll::ProduceContourLine()
 {
     ComputeContourLine* ccL = new ComputeContourLine();
     if(poDataset ==NULL)
         return;
     if(poDataset->GetRasterCount() <= 0)
         return;
     CmlRasterBand* band = new CmlRasterBand(poDataset->GetRasterBand(1));
     ccL->GetDataInfo(band,100);
     ccL->ComputeLines();
     imageLabel->Lineset = &ccL->Doc.LineSet;
     imageLabel->update();
    // delete ccL;


 }

 void CustomScroll::writeimage()
 {
      GDALAllRegister();
      GDALDataset *poDataset = (GDALDataset*)GDALOpen("//home//lw/Desktop//ddd.tif", GA_Update);
      CmlRasterDataset* rds = new CmlRasterDataset(poDataset);
      rds->SaveAsFunc("//home//lw/Desktop//ddd.bmp","bmp");
      delete rds;
 }

 bool CustomScroll::CreatCopiedImage()
 {
     /*
    // if(poDataset == NULL)
    //     return false;
    // GDALDriver* poDriver = poDataset->GetDriver();
     GDALAllRegister();
     GDALDriver *poDriver;
     poDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
     GDALDataset *poDataset = (GDALDataset*)GDALOpen("//home//lw/Desktop//zzz.bmp", GA_Update);
     if(poDriver == NULL)
         return false;
      int nBandCount = poDataset->GetRasterCount();
     int nXSize = poDataset->GetRasterXSize();
     int nYSize = poDataset->GetRasterYSize();
     GDALDataType datatype = poDataset->GetRasterBand(1)->GetRasterDataType();

    GDALDataset *poDestDataset;//= (GDALDataset*)GDALOpen("//home//lw/Desktop//C++Test//Copiedfile", GA_Update);

    poDestDataset = poDriver->Create("//home//lw/Desktop//ddd.tif",poDataset->GetRasterXSize(),poDataset->GetRasterYSize(),
                      poDataset->GetRasterCount(),GDT_Float64,NULL);
int jjj = poDataset->GetRasterCount();
    GDALRasterBand* pband = poDestDataset->GetRasterBand(1);
    double zz = 3;
    pband->RasterIO(GF_Write,0,0,1,1,&zz,1,1,GDT_Float64,0,0);
    poDestDataset->FlushCache();
    //poDestDataset = poDriver->CreateCopy("//home//lw/Desktop//ddd.bmp",poDataset,true,0,0,0);
   // poDestDataset->FlushCache();
double zzz;
    pband->RasterIO(GF_Read,0,0,1,1,&zzz,1,1,GDT_Float64,0,0);
*/
     GDALAllRegister();
          GDALDriver *poDriver;
          poDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
          if( poDriver == NULL )
          {
              return false;
          }


          char* Options=NULL;
          //CString strOption="INTERLEAVE=PIXEL";
          //char*  Options[1];
          //Options[0]=new char[strOption.GetLength()+1];
      //strcpy(Options[0],strOption.GetBuffer(0));

          //char* strOp="INTERLEAVE=PIXEL";
          //char** Options=&strOp;

          //Options�ĺ��壺
          //["INTERLEAVE=PIXEL"]:RGBRGB��ʽ
          //["INTERLEAVE=BAND" RRRRR...GGGG...BBBB
          //m_pDataset = poDriver->Create(FileName,nW,nH,nBands,NBY,/*&Options8*/NULL);
         GDALDataset*  m_pDataset = poDriver->Create("/home/lw/Desktop/outDem.tif",100,100,1,GDT_Float64,/*&Options8*/NULL);

          if( m_pDataset == NULL )
          {
              return false;
          }
          GDALRasterBand* pTempBand = m_pDataset->GetRasterBand( 1 );
          double dTest = 12345;
          pTempBand->RasterIO( GF_Write, 0, 0, 1, 1, &dTest, 1 ,1 ,GDT_Float64, 0, 0);
          m_pDataset->FlushCache();

          double dFetch = -99999999;
          pTempBand->RasterIO( GF_Read, 0, 0, 1, 1, &dFetch, 1, 1, GDT_Float64, 0, 0);


       return true;
 }

 /*
   ����դ�����������ص��ڵ�ǰ���ű�����λ�ڻ����е�λ��
   ����1��������դ�������е�x����
   ����2��������դ�������е�y����
   ����3�������ڻ����е�x����
   ����4�������ڻ����е�y����
*/
 void CustomScroll::RasterLocationToCanvasLocation(double rx,double ry, double& cx,double& cy)
 {
     //cx = rx / scaleFactor + ltincanvas.x;
    // cy = ry / scaleFactor + ltincanvas.y;
   //  rx - RasterRect.left
  //  ��drawlabel�е�drawpointΪ�ο�ԭ�����cx��cy ����0.5��Ϊ������������Ϊ������
   cx =  (rx + 0.5 - (int)ImageLeftTopInRaster.x)/scaleFactor + (ImageLeftTopInRaster.x / scaleFactor + ImageLeftTopInCanvas.x);
   cy =  (ry + 0.5 - (int)ImageLeftTopInRaster.y)/scaleFactor + (ImageLeftTopInRaster.y / scaleFactor + ImageLeftTopInCanvas.y)  ;
   // cx = rx / scaleFactor + RasterRect.left;
   // cy = ry / scaleFactor + RasterRect.top;
    // cx = rx * (RasterRect.right - RasterRect.left) / RasterWidth + RasterRect.left;
    // cy = ry * (RasterRect.bottom - RasterRect.top) / RasterHeight + RasterRect.top;
 }
 void CustomScroll:: CanvasLocationToRasterLocation(double cx,double cy, double& rx,double &ry)
 {
     // RasterTopLeftInCanvas.x ����0.5 / scaleFactor����Ϊ������������Ϊ������
         rx = (cx - (RasterTopLeftInCanvas.x + 0.5 / scaleFactor) ) * scaleFactor   ;
         ry = (cy - (RasterTopLeftInCanvas.y + 0.5 / scaleFactor) ) * scaleFactor   ;

//         double ix;
//         if(RasterRect.left < 0)
//         {
//            ix  = cx - RasterRect.left;
//         }
//         else
//         {
//            ix  = cx ;
//         }

//         double iy;
//         if(RasterRect.top < 0)
//         {
//             iy = cy - RasterRect.top;
//         }
//         else
//         {
//             iy = cy;
//         }
//                 ix  = cx - RasterRect.left;
//                  iy = cy - RasterRect.top;
//         rx = ImageLeftTopInRaster.x + (ix - ImageLeftTopInCanvas.x) * scaleFactor;
//         ry = ImageLeftTopInRaster.y + (iy - ImageLeftTopInCanvas.y) * scaleFactor;

        // rx =(cx /*- RasterRect.left*/ - (ImageLeftTopInRaster.x / scaleFactor + ImageLeftTopInCanvas.x)*scaleFactor) + (int)ImageLeftTopInRaster.x;
        // ry =(cy /*- RasterRect.top*/ - (ImageLeftTopInRaster.y / scaleFactor + ImageLeftTopInCanvas.y)*scaleFactor) + (int)ImageLeftTopInRaster.y;

        // rx = (cx - RasterRect.left - ImageLeftTopInCanvas.x) * scaleFactor;
        // ry = (cy - RasterRect.top - ImageLeftTopInCanvas.y) * scaleFactor;

         // rx = (cx - RasterRect.left - ImageLeftTopInCanvas.x) * scaleFactor;
         // ry = (cy - RasterRect.top - ImageLeftTopInCanvas.y) * scaleFactor;
 }

 // ��ָ��դ�����ݵ����
 void CustomScroll::CenterRasterPoint(double pointx,double pointy)
 {
//         double centerx = scrollArea->width() / 2 + RasterTopLeftInCanvas.x;
//         double centery = scrollArea->height() /2 + RasterTopLeftInCanvas.y;

//         double rx,ry;
//         CanvasLocationToRasterLocation(centerx,centery,rx,ry);
//        double xdis  ;
//         double ydis  ;

//         xdis = pointx - rx;
//         ydis = pointy - ry;
//         RasterTopLeftInCanvas.x -= xdis;
//         RasterTopLeftInCanvas.y -= ydis;

//         int centerx = scrollArea->width() / 2;
//         int centery = scrollArea->height() /2;

//         int xdis = centerx - RasterTopLeftInCanvas.x;
//         int ydis = centery - RasterTopLeftInCanvas.y;
//         double changev = 1;

//         xdis = xdis * changev;
//         ydis = ydis * changev;

//         if(scaleFactor <= 1.0/4096.0 && numSteps <0)
//         {
//             return;
//         }

//         RasterTopLeftInCanvas.x = centerx - xdis;
//         RasterTopLeftInCanvas.y = centery - ydis;

//         scaleFactor = scaleFactor / pow(2, (0 - numSteps));
 //        DrawPicture();
     double disx = scrollArea->width() / 2 * scaleFactor;
     double disy = scrollArea->height() /2 * scaleFactor;

     _mlRECT rt;
     rt.left = pointx - disx;
     rt.right = pointx +disx;
     rt.top = pointy  - disy;
     rt.bottom = pointy + disy;
     ZoomToRect(rt);
 }


 void CustomScroll::LoadImage(char* fileName)
 {
     //read raster file
     if(poDataset !=NULL)
     {
         delete poDataset;
     }
     poDataset = NULL;
     GDALAllRegister();
     poDataset = (GDALDataset *)GDALOpen(fileName,GA_ReadOnly);
     if(poDataset == NULL)
     {
         imageLabel->image = NULL;
         imageLabel->update();
         return;
     }
     //Fetching a Raster Band
     GDALRasterBand  *poBand;
     poBand = poDataset->GetRasterBand( 1 );
     if(poDataset->GetRasterXSize()*poDataset->GetRasterYSize() > 2048 && GDALGetOverviewCount(poBand) == 0 )
     {
         const char *  pszResampling2 = "AVER";	// GAUSS,
         int  nOverviews = 5;
         int  anOverviewList[5] = { 2, 4, 8, 16, 32 };
         int  nListBands = 0;
         int *  panBandList = NULL;
         CPLErr PLInfo;
         // build pyramind
         PLInfo   = GDALBuildOverviews  (poDataset,pszResampling2,nOverviews,anOverviewList,nListBands,panBandList,
                                         GDALDummyProgress   , NULL);
     }
     //Reading Raster Data
     long   nXSize = poBand->GetXSize();
     long   nYSize = poBand->GetYSize();
     RasterWidth = nXSize;
     RasterHeight = nYSize;
     scaleFactor = 1;
     RasterTopLeftInCanvas.x = 0;
     RasterTopLeftInCanvas.y = 0;
     //poBand->ComputeRasterMinMax(1,MinMaxValue);
     GDALComputeRasterMinMax((GDALRasterBandH)poBand,false, MinMaxValue);
     DrawPicture();
 }

 void CustomScroll:: DrawPicture()
 {
     if(poDataset == NULL)
         return;
     CmlRasterDataset rdataset(poDataset);
     GDALRasterBand* band = rdataset.GetRasterBand(1);
     CmlRasterBand rband(band);
     char* pabyData = NULL;
     GDALRasterBand  *poBand;
     poBand = poDataset->GetRasterBand( 1 );
     if(poBand ==NULL)
     {
         return;
     }
     GDALDataType datatype = poBand->GetRasterDataType();
     double imgxsize,imgysize;

     _mlPOINT ltincanvas,ltinraster,rbinraster;
     ComputeRasterRect(this->RasterRect,this->scaleFactor,this->RasterTopLeftInCanvas);
     ComputeImageSizeAndLocation(this->RasterRect,
                                 this->scaleFactor,
                                 imgxsize,imgysize,
                                 ltinraster,
                                 ltincanvas,
                                 rbinraster);
     ImageLeftTopInRaster.x = (int)ltinraster.x;
     ImageLeftTopInRaster.y = (int)ltinraster.y;
     ImageLeftTopInCanvas.x = ltincanvas.x;
     ImageLeftTopInCanvas.y = ltincanvas.y;

    int bandnum = poDataset->GetRasterCount();
    // datasize�����ص��ֽ�����8λ1���ֽ�, 16λ2���ֽ�
     int datasize = rband.m_nPixelDataSize;

     if(image != NULL)
     {
         delete image;
         image = NULL;
     }

     pabyData = new char[((int)imgxsize)*((int)imgysize) * datasize * bandnum];
     double ReadWidth = rbinraster.x - ltinraster.x ;
     double ReadHeight = rbinraster.y - ltinraster.y ;
     if(ReadWidth > imgxsize)
     {
         ReadWidth --;
     }
     if(ReadHeight > imgysize)
     {
         ReadHeight --;
     }
     if(datasize ==2 && bandnum==1)
     {
        // if(scaleFactor > 1)
           if(1)
         {
              if(ReadWidth > (int)ReadWidth)
              {
                  ReadWidth ++;
              }
              if(ReadHeight > (int)ReadHeight)
              {
                  ReadHeight ++;
              }
             poDataset->RasterIO(GF_Read,ltinraster.x,ltinraster.y,ReadWidth, ReadHeight ,pabyData,imgxsize,imgysize,datatype,bandnum,0,0,0,1);
             char* TemppabyData = new char[((int)imgxsize)*((int)imgysize)];
             short* ShortIntDatabuffer = (short*) pabyData;
             int pixelnum = ((int)imgxsize)*((int)imgysize);
             if(MinMaxValue[1]!=MinMaxValue[0])
             {
                 for(int i = 0; i < pixelnum; i++ )
                 {
                     if(ShortIntDatabuffer[i]<MinMaxValue[0])
                     {
                         TemppabyData[i] = 0;
                         continue;
                     }
                     if(ShortIntDatabuffer[i] > MinMaxValue[1])
                     {
                         TemppabyData[i] = 255;
                         continue;
                     }
                     TemppabyData[i] = (ShortIntDatabuffer[i] - MinMaxValue[0]) * 255.0 / (MinMaxValue[1] - MinMaxValue[0]);
                  }
             }
             QImage img ((GByte*)TemppabyData,imgxsize,imgysize,QImage::Format_Indexed8);
             cimage = img;
             //img.setColorTable(ByteMapColorTable);
             cimage.setColorTable(ByteMapColorTable);
             delete pabyData;
             pabyData =NULL;
             //  ����о��ȶ�ʧ
             if(ReadWidth > rbinraster.x - ltinraster.x || ReadHeight > rbinraster.y - ltinraster.y)
             {
                 int dd,zz;
                 imgxsize = imgxsize * ((int)ReadWidth) / (rbinraster.x - ltinraster.x);
                 imgysize = imgysize * ((int)ReadHeight) /( rbinraster.y - ltinraster.y);
                     dd = cimage.width();
                     zz = cimage.height();
                      timage = (cimage.scaled(imgxsize,imgysize));
                      dd = timage.width();
                      zz = timage.height();
                      dd = cimage.width();
                      zz = cimage.height();
                      cimage = timage;
             }
         }
     }
     else
         if(datasize ==1 && bandnum >= 3)
         {
             bandnum = 3;
             int rgbbandmap[3];
             if(ReadWidth > (int)ReadWidth)
             {
                 ReadWidth ++;
             }
             if(ReadHeight > (int)ReadHeight)
             {
                 ReadHeight ++;
             }
             rgbbandmap[0] = 1; rgbbandmap[1] =2;rgbbandmap[2] = 3;
             poDataset->RasterIO(GF_Read,ltinraster.x,ltinraster.y,ReadWidth,ReadHeight ,pabyData,imgxsize,imgysize,datatype,bandnum,rgbbandmap,bandnum,0,1);
             //image = new QImage((GByte*)pabyData , imgxsize,imgysize,QImage::Format_RGB888);
              QImage img((GByte*)pabyData , imgxsize,imgysize,QImage::Format_RGB888);
              cimage = img;
              //  ����о��ȶ�ʧ
              if(ReadWidth > rbinraster.x - ltinraster.x || ReadHeight > rbinraster.y - ltinraster.y)
              {
                  int dd,zz;
                  imgxsize = imgxsize * ((int)ReadWidth) / (rbinraster.x - ltinraster.x);
                  imgysize = imgysize * ((int)ReadHeight) /( rbinraster.y - ltinraster.y);
                  dd = cimage.width();
                  zz = cimage.height();
                  timage = (cimage.scaled(imgxsize,imgysize));
                  dd = timage.width();
                  zz = timage.height();
                  dd = cimage.width();
                  zz = cimage.height();
                  cimage = timage;
              }
         }
         else
             if(datasize == 8 && bandnum == 1)
             {
                 if(ReadWidth > (int)ReadWidth)
                 {
                     ReadWidth ++;
                 }
                 if(ReadHeight > (int)ReadHeight)
                 {
                     ReadHeight ++;
                 }
                poDataset->RasterIO(GF_Read,ltinraster.x,ltinraster.y,ReadWidth, ReadHeight ,pabyData,imgxsize,imgysize,datatype,bandnum,0,0,0,1);
                char* TemppabyData = new char[((int)imgxsize)*((int)imgysize)];
                double* DoubleDatabuffer = (double*) pabyData;
                int pixelnum = ((int)imgxsize)*((int)imgysize);
                if(MinMaxValue[1]!=MinMaxValue[0])
                {
                    for(int i = 0; i < pixelnum; i++ )
                    {
                        if(DoubleDatabuffer[i]<MinMaxValue[0])
                        {
                            TemppabyData[i] = 0;
                            continue;
                        }
                        if(DoubleDatabuffer[i] > MinMaxValue[1])
                        {
                            TemppabyData[i] = 255;
                            continue;
                        }
                        TemppabyData[i] = (DoubleDatabuffer[i] - MinMaxValue[0]) * 255.0 / (MinMaxValue[1] - MinMaxValue[0]);
                     }
                }
                QImage img ((GByte*)TemppabyData,imgxsize,imgysize,QImage::Format_Indexed8);
                img.setColorTable(ByteMapColorTable);
                delete pabyData;
                pabyData =NULL;
                cimage = img;
                //  ����о��ȶ�ʧ
                if(ReadWidth > rbinraster.x - ltinraster.x || ReadHeight > rbinraster.y - ltinraster.y)
                {
                    int dd,zz;
                    imgxsize = imgxsize * ((int)ReadWidth) / (rbinraster.x - ltinraster.x);
                    imgysize = imgysize * ((int)ReadHeight) /( rbinraster.y - ltinraster.y);
                        dd = cimage.width();
                        zz = cimage.height();
                         timage = (cimage.scaled(imgxsize,imgysize));
                         dd = timage.width();
                         zz = timage.height();
                         dd = cimage.width();
                         zz = cimage.height();
                         cimage = timage;
                }
             }
     else
                 if(datasize == 1 && bandnum ==1)
                 {
                     if(ReadWidth > (int)ReadWidth)
                     {
                         ReadWidth ++;
                     }
                     if(ReadHeight > (int)ReadHeight)
                     {
                         ReadHeight ++;
                     }
                    poDataset->RasterIO(GF_Read,ltinraster.x,ltinraster.y,ReadWidth, ReadHeight ,pabyData,imgxsize,imgysize,datatype,bandnum,0,0,0,1);

                    char* TemppabyData = new char[((int)imgxsize)*((int)imgysize)];
                    //char* DoubleDatabuffer = (double*) pabyData;
                    int pixelnum = ((int)imgxsize)*((int)imgysize);
                    if(MinMaxValue[1]!=MinMaxValue[0])
                    {
                        for(int i = 0; i < pixelnum; i++ )
                        {
                            if(pabyData[i]<MinMaxValue[0])
                            {
                                TemppabyData[i] = 0;
                                continue;
                            }
                            if(pabyData[i] > MinMaxValue[1])
                            {
                                TemppabyData[i] = 255;
                                continue;
                            }
                            TemppabyData[i] = (pabyData[i] - MinMaxValue[0]) * 255.0 / (MinMaxValue[1] - MinMaxValue[0]);
                         }
                    }


                    //image = new QImage((GByte*)pabyData , imgxsize,imgysize,QImage::Format_RGB555);
                    QImage img((GByte*)TemppabyData , imgxsize,imgysize,QImage::Format_Indexed8);
                    cimage = img;
                    cimage.setColorTable(ByteMapColorTable);
                    //  ����о��ȶ�ʧ
                    if(ReadWidth > rbinraster.x - ltinraster.x || ReadHeight > rbinraster.y - ltinraster.y)
                    {
                        int dd,zz;
                        imgxsize = imgxsize * ((int)ReadWidth) / (rbinraster.x - ltinraster.x);
                        imgysize = imgysize * ((int)ReadHeight) /( rbinraster.y - ltinraster.y);
                            dd = cimage.width();
                            zz = cimage.height();
                             timage = (cimage.scaled(imgxsize,imgysize));
                             dd = timage.width();
                             zz = timage.height();
                             dd = cimage.width();
                             zz = cimage.height();
                             cimage = timage;
                    }
                 }
     int rightspread =0;
     int bottomspread = 0;
  {
    if(RasterRect.right < scrollArea->width())
    {
        rightspread =scrollArea->width() - RasterRect.right;
    }

    if(RasterRect.bottom < scrollArea->height())
    {
        bottomspread = scrollArea->height() - RasterRect.bottom;
    }
 }
     ScopeChangedByClickScrollBar = false;
     imageLabel->setGeometry(0,0,
                            RasterRect.right - RasterRect.left + ltincanvas.x +  rightspread
                             ,RasterRect.bottom - RasterRect.top + ltincanvas.y + bottomspread
                             );
     // imageLabel->image = image;
     imageLabel->image = &cimage;

     // ��ltinraster����С��ʱ��rasterio�������Զ�ȡ��������ڼ�����ʱ��ҲҪ��ltinraster������ȡ����������ƫ��
     imageLabel->DrawPoint.setX(((int)ltinraster.x) / scaleFactor + ltincanvas.x) ;
     imageLabel->DrawPoint.setY(((int)ltinraster.y) / scaleFactor + ltincanvas.y) ;

      imageLabel->update();


      int yvalue = 0- RasterRect.top;
      int xvalue = 0 - RasterRect.left;

      if(RasterRect.left<0 && rightspread==0)
      {
         // xvalue += 1;
      }
      ScopeChangedByClickScrollBar = false;
      scrollArea->horizontalScrollBar()->setMaximum(RasterRect.right - RasterRect.left + ltincanvas.x  );
      scrollArea->horizontalScrollBar()->setValue(xvalue  );
     // ScopeChangedByClickScrollBar = true;
      if(RasterRect.top <0 && bottomspread==0)
      {
         // yvalue+=1;
      }
      ScopeChangedByClickScrollBar = false;
      scrollArea->verticalScrollBar()->setMaximum(RasterRect.bottom - RasterRect.top + ltincanvas.y   );
      scrollArea->verticalScrollBar()->setValue(yvalue );
      ScopeChangedByClickScrollBar = true;
 }

 void CustomScroll::mousePressEvent(QMouseEvent *event)
 {

     //QMessageBox::information(this, tr("Image Viewer"),
      //                                  tr("Cannot load %1.").arg(""));
     MouseDown = true;
     if(event->button() == Qt::LeftButton)
     {
         MouseLeftButtonDown = true;
     }
     DownPoint.x = event->pos().x();
     DownPoint.y = event->pos().y();

     switch (CurrentToolType)
     {
     case Tool_pan:

        break;
     case Tool_EditMatchPoint:
     {
//         int zzzz = MatchPointList.count();
//         for(int i = 0; i< MatchPointList.count(); i++)
//         {
//             double cx,cy;
//             RasterLocationToCanvasLocation(MatchPointList.at(i).x,
//                                            MatchPointList.at(i).y,
//                                            cx,cy);
//             //cx��cy�õ�������Ϊ��imagelable�е�����ֵ��Ҫת����scrollarea�е�����ֵ
//             //ѡ�е���scrollarea�е�����
//             double dXInscrollarea,dyInscrollarea;
//             if(RasterRect.left<0)
//             {
//                 dXInscrollarea = RasterRect.left + cx;
//             }
//             else
//             {
//                  dXInscrollarea = cx;
//             }
//             if(RasterRect.top < 0)
//             {
//                 dyInscrollarea = RasterRect.top + cy;
//             }
//             else
//             {
//                  dyInscrollarea = cy;
//             }

//            // if(fabs(DownPoint.x - (RasterRect.left + cx)) < 5
//             //        && fabs(DownPoint.y - (RasterRect.top + cy)) < 5)
//             if(fabs(DownPoint.x - dXInscrollarea) < 5
//                                 && fabs(DownPoint.y - dyInscrollarea) < 5)
//             {
//                 SelectedIdxs->clear();
//                 SelectedIdxs->append(i);
//                 MainFrame->UpdateMatchPointTableView(SelectedIdxs);
//                 break;
//             }
//         }

         if(event->button() == Qt::LeftButton )
         {
             for(int i = 0; i<FeatAutoSelectedIdx.size(); i++)
             {
                 int idx = FeatAutoSelectedIdx.at(i);
                 double cx,cy;
                 RasterLocationToCanvasLocation(FeatPtDataSet->m_ImgPtSet.vecPts.at(idx).X,
                                                FeatPtDataSet->m_ImgPtSet.vecPts.at(idx).Y,
                                                cx,cy);
                 //cx��cy�õ�������Ϊ��imagelable�е�����ֵ��Ҫת����scrollarea�е�����ֵ
                 //ѡ�е���scrollarea�е�����
                 double dXInscrollarea,dyInscrollarea;
                 if(scrollArea->RasterRect.left<0)
                 {
                     dXInscrollarea = scrollArea->RasterRect.left + cx;
                 }
                 else
                 {
                      dXInscrollarea = cx;
                 }
                 if(scrollArea->RasterRect.top < 0)
                 {
                     dyInscrollarea = scrollArea->RasterRect.top + cy;
                 }
                 else
                 {
                      dyInscrollarea = cy;
                 }

                 if(fabs(scrollArea->DownPoint.x - dXInscrollarea) < 5
                                     && fabs(scrollArea->DownPoint.y - dyInscrollarea) < 5)
                 {
                     PickedAPoint = true;
                     break;
                 }
             }
             if(PickedAPoint)
             {
                 break;
             }
             for(int i = 0; i< FeatManualSelectedIdx.size(); i++)
             {
                 int idx = FeatManualSelectedIdx.at(i);
                 double cx,cy;
                 RasterLocationToCanvasLocation(FeatPtDataSet->m_ImgPtSet.vecAddPts.at(idx).X,
                                                FeatPtDataSet->m_ImgPtSet.vecAddPts.at(idx).Y,
                                                cx,cy);
                 //cx��cy�õ�������Ϊ��imagelable�е�����ֵ��Ҫת����scrollarea�е�����ֵ
                 //ѡ�е���scrollarea�е�����
                 double dXInscrollarea,dyInscrollarea;
                 if(scrollArea->RasterRect.left<0)
                 {
                     dXInscrollarea = scrollArea->RasterRect.left + cx;
                 }
                 else
                 {
                      dXInscrollarea = cx;
                 }
                 if(scrollArea->RasterRect.top < 0)
                 {
                     dyInscrollarea = scrollArea->RasterRect.top + cy;
                 }
                 else
                 {
                      dyInscrollarea = cy;
                 }

                 if(fabs(scrollArea->DownPoint.x - dXInscrollarea) < 5
                                     && fabs(scrollArea->DownPoint.y - dyInscrollarea) < 5)
                 {
                     PickedAPoint = true;
                     break;
                 }
             }
             break;
         }
     }
     default:
         break;
     }
     emit MousePressSignal(event);



 }
 void CustomScroll::mouseMoveEvent(QMouseEvent * event)
 {
     switch (CurrentToolType)
     {
     case Tool_pan:
         if(MouseDown)
         {

         }
        break;
     case Tool_EditMatchPoint:
     {
//         if(MouseDown/* && PickedAPoint*/)
//         {
//             cout<< "d~~~~"<<endl;
//             //��׽����ʱ�ϵ�
//             if(PickedAPoint)
//             {
//                 // ��׽����ʱӦ��ֻ��һ��ѡ�е�,�༭�Զ����õ���Զ��㼯��ɾ����Ȼ�����ֶ��㼯����ӡ�
//                 if(FeatAutoSelectedIdx.size() == 1)
//                 {
//                     double rx,ry;
//                     CanvasLocationToRasterLocation(event->x(),event->y(),rx,ry);
//    //                 int idx = FeatAutoSelectedIdx.at(0);
//    //                 ULONG lID = FeatPtDataSet->m_ImgPtSet.vecPts.at(idx).lID;
//    //                 FeatAutoSelectedIdx.clear();
//    //                 FeatManualSelectedIdx.clear();
//    //                 FeatPtDataSet->EditAutoPtByIndxe(FeatAutoSelectedIdx.at(0),rx,ry,lID);
//    //                 FeatManualSelectedIdx.append(FeatAutoSelectedIdx.count() - 1);
//    //                 imageLabel->update();

//                      int idx = FeatAutoSelectedIdx.at(0);
//                      ULONG lID = FeatPtDataSet->m_ImgPtSet.vecPts.at(idx).lID;
//                      FeatPtDataSet->EditAutoPtByIndxe(FeatAutoSelectedIdx.at(0),rx,ry,lID);
//                      FeatAutoSelectedIdx.clear();
//                      FeatManualSelectedIdx.clear();
//                      int selectidx = FeatPtDataSet->m_ImgPtSet.vecAddPts.size() - 1;
//                      FeatManualSelectedIdx.append(selectidx);
//                      imageLabel->update();
//                 }
//                 //�����ֶ���
//                 if(FeatManualSelectedIdx.size() == 1)
//                 {
//                     double rx,ry;
//                     CanvasLocationToRasterLocation(event->x(),event->y(),rx,ry);
//    //                 int idx = FeatManualSelectedIdx.at(0);
//    //                 ULONG lID = FeatPtDataSet->m_ImgPtSet.vecPts.at(idx).lID;
//    //                 FeatPtDataSet->EditManualPtByIndxe(idx,rx,ry);
//    //                 imageLabel->update();

//                     int idx = FeatManualSelectedIdx.at(0);
//                     ULONG lID = FeatPtDataSet->m_ImgPtSet.vecPts.at(idx).lID;
//                     FeatPtDataSet->EditManualPtByIndxe(idx,rx,ry);
//                     imageLabel->update();
//                 }
//             }
//         }
         break;
     }
     default:
         break;
     }

 }

 void CustomScroll::mouseReleaseEvent(QMouseEvent *event)
 {
     emit MouseReleaseSignal(event);
     MouseDown = false;
     MouseLeftButtonDown = false;
     //��ͼ���ι���������Ҽ���ʵ��
     if(event->button()== Qt::RightButton && CurrentToolType != Tool_pan)
     {
         _mlPOINT pt;
         pt.x = event->pos().x();
         pt.y = event->pos().y();
         if(pt.x == DownPoint.x && pt.y == DownPoint.y)
         {
            return;
         }
         RasterTopLeftInCanvas.x += pt.x - DownPoint.x;
         RasterTopLeftInCanvas.y += pt.y - DownPoint.y;
         DrawPicture();
     }

     switch (CurrentToolType)
     {
     case Tool_pan:
     {
         _mlPOINT pt;
         pt.x = event->pos().x();
         pt.y = event->pos().y();
         if(pt.x == DownPoint.x && pt.y == DownPoint.y)
         {
            break;
         }
         RasterTopLeftInCanvas.x += pt.x - DownPoint.x;
         RasterTopLeftInCanvas.y += pt.y - DownPoint.y;

         if(event->button()== Qt::RightButton)
         {
             RasterTopLeftInCanvas.x --;
         }
         else
             if(event->button()==Qt::MidButton)
             {
                 RasterTopLeftInCanvas.x ++;
             }
         DrawPicture();
        break;
     }
     case Tool_EditMatchPoint:
     {
         if(PickedAPoint)
         {
             PickedAPoint = false;
             if(scrollArea == MainFrame->scrollArea)
             {
                 MainFrame->AddLeftMatchPoints();
             }
             if(scrollArea == MainFrame->RightScrollArea)
             {
                 MainFrame->AddRightMatchPoints();
             }
             MainFrame->UpdateFeatPtTableView();

             break;
         }
     }
     default:
         break;
     }

 }

 void CustomScroll::wheelEvent(QWheelEvent *event)
 {
    //QMessageBox::information(this, tr("Image Viewer"),
     //                                 tr("Cannot load %1.").arg(""));

     int numDegrees = event->delta() / 8;
         int numSteps = numDegrees / 15;
         int centerx = scrollArea->width() / 2;
         int centery = scrollArea->height() /2;
         QRect rt = scrollArea->rect();
         int xdis = centerx - RasterTopLeftInCanvas.x;
         int ydis = centery - RasterTopLeftInCanvas.y;
         double changev = pow(2, (0 - numSteps));

         xdis = xdis * changev;
         ydis = ydis * changev;

         if(scaleFactor <= 1.0/4096.0 && numSteps <0)
         {
             return;
         }

         RasterTopLeftInCanvas.x = centerx - xdis;
         RasterTopLeftInCanvas.y = centery - ydis;

         scaleFactor = scaleFactor / pow(2, (0 - numSteps));

         DrawPicture();
 }
 void CustomScroll:: paintEvent ( QPaintEvent * event )
 {
    // DrawPicture();
 }
 void CustomScroll::resizeEvent(QResizeEvent* event)
{

    int w,oldw,h,oldh;
    w = event->size().width();
    oldw = event->oldSize().width();
    h = event->size().height();
    oldh = event->oldSize().height();


    //if(event->size().width() > event->oldSize().width()
     //       || event->size().height()> event->oldSize().height())
    {
       // DrawPicture2();
    }
}
 void CustomScroll::keyPressEvent ( QKeyEvent * event )
 {
     if(event->key() == Qt::Key_Delete)
     {
         DeleteSelectedFeatPt();
     }
 }

void CustomScroll::scrollContentsBy(int dx,int dy)
{
    QScrollArea::scrollContentsBy(dx, dy);

    if(ScopeChangedByClickScrollBar)
    {
        // ���ֱ����RasterTopLeftInCanvas��xyֵ�Ӽ�dx��dy�������ʾ���⣬��dx��dy��һ�ͼ�һ���Խ��������ԭ������Ϊ��֤dx��dy���ر仯һ��ͼƬ�ظ�ԭλ���������С��������ͬ����
        if( ( dx == 0 )||( dy == 0))
        {
            int n = 2;
        }
        if(dx != 0)
        {
            if(dx < 0)
            {
                RasterTopLeftInCanvas.x += dx+1;
            }
            else
            {
                RasterTopLeftInCanvas.x += dx-1;
            }

        }
        if(dy!= 0)
        {
            if(dy < 0)
            {
                 RasterTopLeftInCanvas.y += dy+1;
            }
            else
            {
                 RasterTopLeftInCanvas.y += dy-1;
            }
        }
        DrawPicture();
    }
}
// �˺�������к���������ε�����Ҽ���mousepress�¼�
void CustomScroll::contextMenuEvent(QContextMenuEvent *event)
{

//    QMenu menu(this);
//    menu.addAction(ActDeleteSelectedPts);
//    menu.exec(event->globalPos());
}

void CustomScroll::DrawLabelMouseMoveSlot(int x, int y)
{
//    int dx = ImageLeftTopInCanvas.x + x - RasterRect.left;
//    int dy = ImageLeftTopInCanvas.y + y - RasterRect.top;
    emit DrawLabelMouseMoveSignal(x,y);
}

void CustomScroll::DeleteSelectedFeatPt()
{
//    for(int i = 0; i< FeatAutoSelectedIdx.count(); i++)
//    {
//        FeatPtDataSet->DelAutoPtByIndex(FeatAutoSelectedIdx.at(i));
//    }
//    for(int i = 0; i< FeatManualSelectedIdx.count(); i++)
//    {
//        FeatPtDataSet->DelManualPtByIndex(FeatManualSelectedIdx.at(i));
//    }
    //imageLabel->update();
    emit DelSelectedPts();
}

void CustomScroll:: ZoomToRect(_mlRECT rasterscoperect)
{

    double oldlx = RasterTopLeftInCanvas.x;
    double oldly = RasterTopLeftInCanvas.y;
    double oldscale = scaleFactor;

    double scopewidth = rasterscoperect.right - rasterscoperect.left;
    double scopeheight = rasterscoperect.bottom - rasterscoperect.top;

     double xscale =   scopewidth / scrollArea->width();
     double yscale =   scopeheight / scrollArea->height() ;
    double scale = (xscale > yscale)? xscale:yscale;
    RasterTopLeftInCanvas.x = (0 - rasterscoperect.left) / scale ;
    RasterTopLeftInCanvas.y = (0 - rasterscoperect.top) / scale ;
   // RasterTopLeftInCanvas.x = ( 0 - (rasterscoperect.right + rasterscoperect.left)/2) / scale ;
   // RasterTopLeftInCanvas.y = ( 0 -(rasterscoperect.bottom + rasterscoperect.top)/2) / scale ;
    //���������ʱ�����drawpicture�����������ʾ����
    scaleFactor = scale;
    if(fabs(oldlx - RasterTopLeftInCanvas.x )< 0.000001 &&
         fabs(oldly - RasterTopLeftInCanvas.y) < 0.000001    &&
            fabs(oldscale - scale)<0.00001)
    {
        return;
    }
    DrawPicture();
}
