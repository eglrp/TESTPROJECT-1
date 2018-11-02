using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing.Imaging;
using System.Windows.Forms;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;


namespace CannyEdgeDetectionCSharp
{
    class ClsCanny
    {
        public int Width, Height;
        public Bitmap Obj;
        public int[,] GreyImage;
        //Gaussian Kernel Data
        int[,] GaussianKernel;
        int KernelWeight;
        int KernelSize = 5;
        double Sigma = 1;   // for N=2 Sigma =0.85  N=5 Sigma =1, N=9 Sigma = 2    2*Sigma = (int)N/2
        //Canny Edge Detection Parameters
        double MaxHysteresisThresh, MinHysteresisThresh;
        public double[,] DerivativeX;
        public double[,] DerivativeY;
        public int[,] FilteredImage;
        public double[,] Gradient;
        public double[,] NonMax;
        public int[,] PostHysteresis;
        int[,] EdgePoints;
        public double[,] GNH;
        public double[,] GNL;
        public int[,] EdgeMap;
        public int[,] VisitedMap;

        public ClsCanny(Bitmap Input)
        {
            // Gaussian and Canny Parameters
            MaxHysteresisThresh = 20F;
            MinHysteresisThresh = 10F;
            Obj = Input;
            Width = Obj.Width;
            Height = Obj.Height;
            EdgeMap = new int[Width, Height];
            VisitedMap = new int[Width, Height];

            ReadImage();
            DetectCannyEdges();
            return;
        }

        public ClsCanny(Bitmap Input, double Th, double Tl)
        {

            // Gaussian and Canny Parameters

            MaxHysteresisThresh = Th;
            MinHysteresisThresh = Tl;

            Obj = Input;
            Width = Obj.Width;
            Height = Obj.Height;

            EdgeMap = new int[Width, Height];
            VisitedMap = new int[Width, Height];

            ReadImage();
            DetectCannyEdges();
            return;
        }

        public ClsCanny(Bitmap Input, double Th, double Tl, int GaussianMaskSize, double SigmaforGaussianKernel)
        {

            // Gaussian and Canny Parameters

            MaxHysteresisThresh = Th;
            MinHysteresisThresh = Tl;
            KernelSize = GaussianMaskSize;
            Sigma = SigmaforGaussianKernel;
            Obj = Input;
            Width = Obj.Width;
            Height = Obj.Height;

            EdgeMap = new int[Width, Height];
            VisitedMap = new int[Width, Height];

            ReadImage();
            DetectCannyEdges();
            return;
        }

        private void ReadImage()
        {
            int i, j;
            GreyImage = new int[Obj.Width, Obj.Height];  //[Row,Column]
            Bitmap image = Obj;
            BitmapData bitmapData1 = image.LockBits(new Rectangle(0, 0, image.Width, image.Height),
                                     ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
            unsafe
            {
                byte* imagePointer1 = (byte*)bitmapData1.Scan0;

                for (i = 0; i < bitmapData1.Height; i++)
                {
                    for (j = 0; j < bitmapData1.Width; j++)
                    {
                        GreyImage[j, i] = (int)((imagePointer1[0] + imagePointer1[1] + imagePointer1[2]) / 3.0);
                        //4 bytes per pixel
                        imagePointer1 += 4;
                    }//end for j
                    //4 bytes per pixel
                    imagePointer1 += bitmapData1.Stride - (bitmapData1.Width * 4);
                }//end for i
            }//end unsafe
            image.UnlockBits(bitmapData1);
            return;
        }

        private void GenerateGaussianKernel(int N, double S, out int Weight)
        {

            double Sigma = S;
            double pi;
            pi = (double)Math.PI;
            int i, j;
            int SizeofKernel = N;

            double[,] Kernel = new double[N, N];
            GaussianKernel = new int[N, N];
            double[,] OP = new double[N, N];
            double D1, D2;


            D1 = 1 / (2 * pi * Sigma * Sigma);
            D2 = 2 * Sigma * Sigma;

            double min = 1000;

            for (i = -SizeofKernel / 2; i <= SizeofKernel / 2; i++)
            {
                for (j = -SizeofKernel / 2; j <= SizeofKernel / 2; j++)
                {
                    Kernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j] = ((1 / D1) * (double)Math.Exp(-(i * i + j * j) / D2));
                    if (Kernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j] < min)
                        min = Kernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j];

                }
            }
            int mult = (int)(1 / min);
            int sum = 0;
            if ((min > 0) && (min < 1))
            {

                for (i = -SizeofKernel / 2; i <= SizeofKernel / 2; i++)
                {
                    for (j = -SizeofKernel / 2; j <= SizeofKernel / 2; j++)
                    {
                        Kernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j] = (double)Math.Round(Kernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j] * mult, 0);
                        GaussianKernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j] = (int)Kernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j];
                        sum = sum + GaussianKernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j];
                    }

                }

            }
            else
            {
                sum = 0;
                for (i = -SizeofKernel / 2; i <= SizeofKernel / 2; i++)
                {
                    for (j = -SizeofKernel / 2; j <= SizeofKernel / 2; j++)
                    {
                        Kernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j] = (double)Math.Round(Kernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j], 0);
                        GaussianKernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j] = (int)Kernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j];
                        sum = sum + GaussianKernel[SizeofKernel / 2 + i, SizeofKernel / 2 + j];
                    }

                }

            }
            //Normalizing kernel Weight
            Weight = sum;

            return;
        }

        private int[,] GaussianFilter(int[,] Data)
        {
            GenerateGaussianKernel(KernelSize, Sigma, out KernelWeight);

            int[,] Output = new int[Width, Height];
            int i, j, k, l;
            int Limit = KernelSize / 2;

            double Sum = 0;


            Output = Data; // Removes Unwanted Data Omission due to kernel bias while convolution


            for (i = Limit; i <= ((Width - 1) - Limit); i++)
            {
                for (j = Limit; j <= ((Height - 1) - Limit); j++)
                {
                    Sum = 0;
                    for (k = -Limit; k <= Limit; k++)
                    {

                        for (l = -Limit; l <= Limit; l++)
                        {
                            Sum = Sum + ((double)Data[i + k, j + l] * GaussianKernel[Limit + k, Limit + l]);

                        }
                    }
                    Output[i, j] = (int)(Math.Round(Sum / (double)KernelWeight));
                }

            }


            return Output;
        }

        private double[,] Differentiate(int[,] Data, int[,] Filter)
        {
            int i, j, k, l, Fh, Fw;

            Fw = Filter.GetLength(0);
            Fh = Filter.GetLength(1);
            double sum = 0;
            double[,] Output = new double[Width, Height];

            for (i = Fw / 2; i <= (Width - Fw / 2) - 1; i++)
            {
                for (j = Fh / 2; j <= (Height - Fh / 2) - 1; j++)
                {
                    sum = 0;
                    for (k = -Fw / 2; k <= Fw / 2; k++)
                    {
                        for (l = -Fh / 2; l <= Fh / 2; l++)
                        {
                            sum = sum + Data[i + k, j + l] * Filter[Fw / 2 + k, Fh / 2 + l];


                        }
                    }
                    Output[i, j] = sum;

                }

            }
            return Output;

        }

        private void DetectCannyEdges()
        {
            Gradient = new double[Width, Height];
            NonMax = new double[Width, Height];
            PostHysteresis = new int[Width, Height];

            DerivativeX = new double[Width, Height];
            DerivativeY = new double[Width, Height];

            //Gaussian Filter Input Image 

            FilteredImage = GaussianFilter(GreyImage);
            //Sobel Masks
            int[,] Dx = {{1,0,-1},
                         {1,0,-1},
                         {1,0,-1}};

            int[,] Dy = {{1,1,1},
                         {0,0,0},
                         {-1,-1,-1}};


            DerivativeX = Differentiate(FilteredImage, Dx);
            DerivativeY = Differentiate(FilteredImage, Dy);

            int i, j;

            //Compute the gradient magnitude based on derivatives in x and y:
            for (i = 0; i <= (Width - 1); i++)
            {
                for (j = 0; j <= (Height - 1); j++)
                {
                    Gradient[i, j] = (double)Math.Sqrt((DerivativeX[i, j] * DerivativeX[i, j]) + (DerivativeY[i, j] * DerivativeY[i, j]));

                }

            }
            // Perform Non maximum suppression:
            // NonMax = Gradient;

            for (i = 0; i <= (Width - 1); i++)
            {
                for (j = 0; j <= (Height - 1); j++)
                {
                    NonMax[i, j] = Gradient[i, j];
                }
            }

            int Limit = KernelSize / 2;
            int r, c;
            double Tangent;


            for (i = Limit; i <= (Width - Limit) - 1; i++)
            {
                for (j = Limit; j <= (Height - Limit) - 1; j++)
                {

                    if (DerivativeX[i, j] == 0)
                        Tangent = 90F;
                    else
                        Tangent = (double)(Math.Atan(DerivativeY[i, j] / DerivativeX[i, j]) * 180 / Math.PI); //rad to degree



                    //Horizontal Edge
                    if (((-22.5 < Tangent) && (Tangent <= 22.5)) || ((157.5 < Tangent) && (Tangent <= -157.5)))
                    {
                        if ((Gradient[i, j] < Gradient[i, j + 1]) || (Gradient[i, j] < Gradient[i, j - 1]))
                            NonMax[i, j] = 0;
                    }


                    //Vertical Edge
                    if (((-112.5 < Tangent) && (Tangent <= -67.5)) || ((67.5 < Tangent) && (Tangent <= 112.5)))
                    {
                        if ((Gradient[i, j] < Gradient[i + 1, j]) || (Gradient[i, j] < Gradient[i - 1, j]))
                            NonMax[i, j] = 0;
                    }

                    //+45 Degree Edge
                    if (((-67.5 < Tangent) && (Tangent <= -22.5)) || ((112.5 < Tangent) && (Tangent <= 157.5)))
                    {
                        if ((Gradient[i, j] < Gradient[i + 1, j - 1]) || (Gradient[i, j] < Gradient[i - 1, j + 1]))
                            NonMax[i, j] = 0;
                    }

                    //-45 Degree Edge
                    if (((-157.5 < Tangent) && (Tangent <= -112.5)) || ((67.5 < Tangent) && (Tangent <= 22.5)))
                    {
                        if ((Gradient[i, j] < Gradient[i + 1, j + 1]) || (Gradient[i, j] < Gradient[i - 1, j - 1]))
                            NonMax[i, j] = 0;
                    }

                }
            }


            //PostHysteresis = NonMax;
            for (r = Limit; r <= (Width - Limit) - 1; r++)
            {
                for (c = Limit; c <= (Height - Limit) - 1; c++)
                {

                    PostHysteresis[r, c] = (int)NonMax[r, c];
                }

            }

            //Find Max and Min in Post Hysterisis
            double min, max;
            min = 100;
            max = 0;
            for (r = Limit; r <= (Width - Limit) - 1; r++)
                for (c = Limit; c <= (Height - Limit) - 1; c++)
                {
                    if (PostHysteresis[r, c] > max)
                    {
                        max = PostHysteresis[r, c];
                    }

                    if ((PostHysteresis[r, c] < min) && (PostHysteresis[r, c] > 0))
                    {
                        min = PostHysteresis[r, c];
                    }
                }

            GNH = new double[Width, Height];
            GNL = new double[Width, Height]; ;
            EdgePoints = new int[Width, Height];

            for (r = Limit; r <= (Width - Limit) - 1; r++)
            {
                for (c = Limit; c <= (Height - Limit) - 1; c++)
                {
                    if (PostHysteresis[r, c] >= MaxHysteresisThresh)
                    {

                        EdgePoints[r, c] = 1;
                        GNH[r, c] = 255;
                    }
                    if ((PostHysteresis[r, c] < MaxHysteresisThresh) && (PostHysteresis[r, c] >= MinHysteresisThresh))
                    {

                        EdgePoints[r, c] = 2;
                        GNL[r, c] = 255;

                    }

                }

            }

            HysterisisThresholding(EdgePoints);

            for (i = 0; i <= (Width - 1); i++)
                for (j = 0; j <= (Height - 1); j++)
                {
                    EdgeMap[i, j] = EdgeMap[i, j] * 255;
                }

            return;

        }

        private void HysterisisThresholding(int[,] Edges)
        {

            int i, j;
            int Limit = KernelSize / 2;


            for (i = Limit; i <= (Width - 1) - Limit; i++)
                for (j = Limit; j <= (Height - 1) - Limit; j++)
                {
                    if (Edges[i, j] == 1)
                    {
                        EdgeMap[i, j] = 1;

                    }

                }

            for (i = Limit; i <= (Width - 1) - Limit; i++)
            {
                for (j = Limit; j <= (Height - 1) - Limit; j++)
                {
                    if (Edges[i, j] == 1)
                    {
                        EdgeMap[i, j] = 1;
                        Travers(i, j);
                        VisitedMap[i, j] = 1;
                    }
                }
            }




            return;
        }

        private void Travers(int X, int Y)
        {


            if (VisitedMap[X, Y] == 1)
            {
                return;
            }

            //1
            if (EdgePoints[X + 1, Y] == 2)
            {
                EdgeMap[X + 1, Y] = 1;
                VisitedMap[X + 1, Y] = 1;
                Travers(X + 1, Y);
                return;
            }
            //2
            if (EdgePoints[X + 1, Y - 1] == 2)
            {
                EdgeMap[X + 1, Y - 1] = 1;
                VisitedMap[X + 1, Y - 1] = 1;
                Travers(X + 1, Y - 1);
                return;
            }

            //3

            if (EdgePoints[X, Y - 1] == 2)
            {
                EdgeMap[X, Y - 1] = 1;
                VisitedMap[X, Y - 1] = 1;
                Travers(X, Y - 1);
                return;
            }

            //4

            if (EdgePoints[X - 1, Y - 1] == 2)
            {
                EdgeMap[X - 1, Y - 1] = 1;
                VisitedMap[X - 1, Y - 1] = 1;
                Travers(X - 1, Y - 1);
                return;
            }
            //5
            if (EdgePoints[X - 1, Y] == 2)
            {
                EdgeMap[X - 1, Y] = 1;
                VisitedMap[X - 1, Y] = 1;
                Travers(X - 1, Y);
                return;
            }
            //6
            if (EdgePoints[X - 1, Y + 1] == 2)
            {
                EdgeMap[X - 1, Y + 1] = 1;
                VisitedMap[X - 1, Y + 1] = 1;
                Travers(X - 1, Y + 1);
                return;
            }
            //7
            if (EdgePoints[X, Y + 1] == 2)
            {
                EdgeMap[X, Y + 1] = 1;
                VisitedMap[X, Y + 1] = 1;
                Travers(X, Y + 1);
                return;
            }
            //8

            if (EdgePoints[X + 1, Y + 1] == 2)
            {
                EdgeMap[X + 1, Y + 1] = 1;
                VisitedMap[X + 1, Y + 1] = 1;
                Travers(X + 1, Y + 1);
                return;
            }


            //VisitedMap[X, Y] = 1;
            return;
        }

        public Bitmap GetImageFromArray(int[,] GreyImage)
        {
            int i, j;
            int W, H;
            W = GreyImage.GetLength(0);
            H = GreyImage.GetLength(1);
            Bitmap image = new Bitmap(W, H);
            BitmapData bitmapData1 = image.LockBits(new Rectangle(0, 0, W, H),
                                     ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
            unsafe
            {

                byte* imagePointer1 = (byte*)bitmapData1.Scan0;

                for (i = 0; i < bitmapData1.Height; i++)
                {
                    for (j = 0; j < bitmapData1.Width; j++)
                    {
                        // write the logic implementation here
                        imagePointer1[0] = (byte)GreyImage[j, i];
                        imagePointer1[1] = (byte)GreyImage[j, i];
                        imagePointer1[2] = (byte)GreyImage[j, i];
                        imagePointer1[3] = (byte)255;
                        //4 bytes per pixel
                        imagePointer1 += 4;
                    }   //end for j
                    //4 bytes per pixel
                    imagePointer1 += (bitmapData1.Stride - (bitmapData1.Width * 4));
                }//End for i
            }//end unsafe
            image.UnlockBits(bitmapData1);
            return image;// col;
        }      // Display Grey Image

        //Canny Class Ends
        /// <summary>
        /// ��Դͼ��ҶȻ�����ת��Ϊ8λ�Ҷ�ͼ��
        /// </summary>
        /// <param name="original"> Դͼ�� </param>
        /// <returns> 8λ�Ҷ�ͼ�� </returns>
        public static Bitmap RgbToGrayScale(Bitmap original)
        {
            if (original != null)
            {
                // ��Դͼ���ڴ���������
                Rectangle rect = new Rectangle(0, 0, original.Width, original.Height);
                BitmapData bmpData = original.LockBits(rect, ImageLockMode.ReadOnly,
                     original.PixelFormat);

                // ��ȡͼ�����
                int width = bmpData.Width;
                int height = bmpData.Height;
                int stride = bmpData.Stride;  // ɨ���ߵĿ��
                int offset = stride - width * 3;  // ��ʾ�����ɨ���߿�ȵļ�϶
                IntPtr ptr = bmpData.Scan0;   // ��ȡbmpData���ڴ���ʼλ��
                int scanBytes = stride * height;  // ��stride��ȣ���ʾ�����ڴ�����Ĵ�С

                // �ֱ���������λ��ָ�룬ָ��Դ�����Ŀ������
                int posScan = 0, posDst = 0;
                byte[] rgbValues = new byte[scanBytes];  // ΪĿ����������ڴ�
                Marshal.Copy(ptr, rgbValues, 0, scanBytes);  // ��ͼ�����ݿ�����rgbValues��
                // ����Ҷ�����
                byte[] grayValues = new byte[width * height]; // ����δ�ÿռ䡣
                // ����Ҷ�����
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        double temp = rgbValues[posScan++] * 0.11 +
                            rgbValues[posScan++] * 0.59 +
                            rgbValues[posScan++] * 0.3;
                        grayValues[posDst++] = (byte)temp;
                    }
                    // ����ͼ������ÿ��δ�ÿռ���ֽڣ�length = stride - width * bytePerPixel
                    posScan += offset;
                }

                // �ڴ����
                Marshal.Copy(rgbValues, 0, ptr, scanBytes);
                original.UnlockBits(bmpData);  // �����ڴ�����

                // ����8λ�Ҷ�λͼ
                Bitmap retBitmap = BuiltGrayBitmap(grayValues, width, height);
                return retBitmap;
            }
            else
            {
                return null;
            }
        }

        /// <summary>
        /// �ûҶ������½�һ��8λ�Ҷ�ͼ��
        /// http://www.cnblogs.com/spadeq/archive/2009/03/17/1414428.html
        /// </summary>
        /// <param name="rawValues"> �Ҷ�����(length = width * height)�� </param>
        /// <param name="width"> ͼ���ȡ� </param>
        /// <param name="height"> ͼ��߶ȡ� </param>
        /// <returns> �½���8λ�Ҷ�λͼ�� </returns>
        private static Bitmap BuiltGrayBitmap(byte[] rawValues, int width, int height)
        {
            // �½�һ��8λ�Ҷ�λͼ���������ڴ��������
            Bitmap bitmap = new Bitmap(width, height, PixelFormat.Format8bppIndexed);
            BitmapData bmpData = bitmap.LockBits(new Rectangle(0, 0, width, height),
                 ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);

            // ����ͼ�����
            int offset = bmpData.Stride - bmpData.Width;        // ����ÿ��δ�ÿռ��ֽ���
            IntPtr ptr = bmpData.Scan0;                         // ��ȡ�׵�ַ
            int scanBytes = bmpData.Stride * bmpData.Height;    // ͼ���ֽ��� = ɨ���ֽ��� * �߶�
            byte[] grayValues = new byte[scanBytes];            // Ϊͼ�����ݷ����ڴ�

            // Ϊͼ�����ݸ�ֵ
            int posSrc = 0, posScan = 0;                        // rawValues��grayValues������
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    grayValues[posScan++] = rawValues[posSrc++];
                }
                // ����ͼ������ÿ��δ�ÿռ���ֽڣ�length = stride - width * bytePerPixel
                posScan += offset;
            }

            // �ڴ����
            Marshal.Copy(grayValues, 0, ptr, scanBytes);
            bitmap.UnlockBits(bmpData);  // �����ڴ�����

            // �޸�����λͼ����������α���޸�Ϊ�Ҷ�
            ColorPalette palette;
            // ��ȡһ��Format8bppIndexed��ʽͼ���Palette����
            using (Bitmap bmp = new Bitmap(1, 1, PixelFormat.Format8bppIndexed))
            {
                palette = bmp.Palette;
            }
            for (int i = 0; i < 256; i++)
            {
                palette.Entries[i] = Color.FromArgb(i, i, i);
            }
            // �޸�����λͼ��������
            bitmap.Palette = palette;

            return bitmap;
        }
    }

    /// <summary>
    /// ͼ��ֱ��ͼ������
    /// </summary>
    class ClsHistogram
    {
        Bitmap sourceImg = null;

        int width = 0;    //Դͼ���
        int height = 0;   //Դͼ�߶�
        int bytes = 0;
        int grayLevels = 0;// ͼ��Ҷȼ���        
        int[] histogram = null;// ֱ��ͼ        
        float[] cumulativeHistogram = null;// ��һ�����ۻ�ֱ��ͼ        
        byte[] mapPixel = null;// ����-�Ҷ� ӳ���        
        int[] newHistogram = null;  // ��ֱ��ͼ
        int maxValue = 0;   //�Ҷ����ֵ

        /// <summary>
        /// ��ʼ��������ͼ��
        /// </summary>
        /// <param name="img">������ͼ��</param>
        /// <param name="bitNum">Դͼλ��</param>
        public ClsHistogram(Bitmap img, byte bitNum)
        {
            if (null == img)
                throw new Exception("���ܶԷ�ͼ�������ȡֱ��ͼ��");
            if (0 != (bitNum % 8))
                throw new Exception("Դͼλ����������! ����Ϊ8��������.");

            sourceImg = img;

            width = sourceImg.Width;    //Դͼ���
            height = sourceImg.Height;  //Դͼ�߶�
            bytes = width * height;

            BitmapData bmData = sourceImg.LockBits(new Rectangle(0, 0, width, height),
                    ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);

            IntPtr ptr = bmData.Scan0;
            byte[] grayValues = new byte[bytes];
            System.Runtime.InteropServices.Marshal.Copy(ptr, grayValues, 0, bytes);

            grayLevels = 2 << (bitNum - 1);   //ͼ��Ҷȼ���
            histogram = new int[grayLevels];     //ֱ��ͼ
            cumulativeHistogram = new float[grayLevels];  //�ۻ�ֱ��ͼ

            maxValue = 0;

            byte temp;
            for (int i = 0; i < bytes; i++) //2.�г�ԭʼֱ��ͼ
            {
                temp = grayValues[i];
                histogram[temp]++;
            }

            cumulativeHistogram[0] = histogram[0] * 1.0F / bytes; //��һ��
            for (int i = 1; i < grayLevels; i++) //3.��ȡ�ۻ�ֱ��ͼ
            {
                /** ������Ҷ�ֵ **/
                if (histogram[i] > maxValue)
                {
                    maxValue = histogram[i];
                }

                cumulativeHistogram[i] = cumulativeHistogram[i - 1] + histogram[i] * 1.0F / bytes;   //�ۻ�
                //cumulativeHistogram[i] /= bytes * 1.0F;  
            }

            System.Runtime.InteropServices.Marshal.Copy(grayValues, 0, ptr, bytes);
            sourceImg.UnlockBits(bmData);
        }

        /// <summary>
        /// ֱ��ͼ���⻯
        /// </summary>
        /// <returns>���⻯֮���ͼ��</returns>
        public Image HistogramEqualization()
        {
            mapPixel = new byte[grayLevels];
            newHistogram = new int[grayLevels];

            byte temp;
            for (int i = 0; i < grayLevels; i++)    //4.ȡ��
            {
                temp = (byte)((grayLevels - 1) * cumulativeHistogram[i] + 0.5F); //���¼��㲢ӳ��
                mapPixel[i] = temp;

                newHistogram[temp] += histogram[i];
            }

            BitmapData bmData = sourceImg.LockBits(new Rectangle(0, 0, width, height),
                    ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            IntPtr ptr = bmData.Scan0;
            byte[] grayValues = new byte[bytes];
            System.Runtime.InteropServices.Marshal.Copy(ptr, grayValues, 0, bytes);

            for (int i = 0; i < bytes; i++) //���·ֲ���ɫ
            {
                temp = grayValues[i];
                grayValues[i] = (byte)mapPixel[temp];
            }

            System.Runtime.InteropServices.Marshal.Copy(grayValues, 0, ptr, bytes);
            sourceImg.UnlockBits(bmData);

            histogram = newHistogram;

            return sourceImg;
        }

        //����ӦѰ��CANNY�ĸߵ���ֵ
        public void adaptiveThreshold(out double dbHigh, out double dbLow)
        {
            dbHigh = dbLow = double.NaN;
            if (cumulativeHistogram == null)
            {
                return;
            }

            double dbThreshold = 0.7;
            double dbCoef = 0.4;
            for (int i = 0; i < cumulativeHistogram.Length; i++)
            {
                if (cumulativeHistogram[i] > dbThreshold)
                {
                    dbHigh = i;
                    dbLow = dbHigh * dbCoef;
                    break;
                }
            }

            return;
        }
    }
}
