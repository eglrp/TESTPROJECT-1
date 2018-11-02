using System;
using System.Drawing;
using System.Runtime.InteropServices;
using ESRI.ArcGIS.ADF.BaseClasses;
using ESRI.ArcGIS.ADF.CATIDs;
using ESRI.ArcGIS.Controls;
using System.IO;
using ESRI.ArcGIS.Geodatabase;
using ESRI.ArcGIS.Carto;
using ESRI.ArcGIS.DataSourcesFile;
using ESRI.ArcGIS.esriSystem;
using ESRI.ArcGIS.SystemUI;
using ESRI.ArcGIS.Geometry;
using ESRI.ArcGIS.Display;
using System.Drawing.Text;
using stdole;
using System.Windows.Forms;

namespace LibEngineCmd
{
    /// <summary>
    /// Summary description for CmdNorthArrowAttribute.
    /// </summary>
    [Guid("34948609-22f4-4cb3-b6b6-bc888f3e9726")]
    [ClassInterface(ClassInterfaceType.None)]
    [ProgId("CustomCE.CmdElementAttribute")]
    public sealed class CmdElementAttribute : BaseCommand
    {
        #region COM Registration Function(s)
        [ComRegisterFunction()]
        [ComVisible(false)]
        static void RegisterFunction(Type registerType)
        {
            // Required for ArcGIS Component Category Registrar support
            ArcGISCategoryRegistration(registerType);

            //
            // TODO: Add any COM registration code here
            //
        }

        [ComUnregisterFunction()]
        [ComVisible(false)]
        static void UnregisterFunction(Type registerType)
        {
            // Required for ArcGIS Component Category Registrar support
            ArcGISCategoryUnregistration(registerType);

            //
            // TODO: Add any COM unregistration code here
            //
        }

        #region ArcGIS Component Category Registrar generated code
        /// <summary>
        /// Required method for ArcGIS Component Category registration -
        /// Do not modify the contents of this method with the code editor.
        /// </summary>
        private static void ArcGISCategoryRegistration(Type registerType)
        {
            string regKey = string.Format("HKEY_CLASSES_ROOT\\CLSID\\{{{0}}}", registerType.GUID);
            ControlsCommands.Register(regKey);

        }
        /// <summary>
        /// Required method for ArcGIS Component Category unregistration -
        /// Do not modify the contents of this method with the code editor.
        /// </summary>
        private static void ArcGISCategoryUnregistration(Type registerType)
        {
            string regKey = string.Format("HKEY_CLASSES_ROOT\\CLSID\\{{{0}}}", registerType.GUID);
            ControlsCommands.Unregister(regKey);

        }

        #endregion
        #endregion

        private IHookHelper m_hookHelper;

        string[] SymbolStyle;
        public CmdElementAttribute(string[] symbolstyle)
        {
            //
            // TODO: Define values for the public properties
            //
            base.m_category = "CustomCE"; //localizable text
            base.m_caption = "Ҫ������";  //localizable text
            base.m_message = "�������";  //localizable text 
            base.m_toolTip = "Ҫ������";  //localizable text 
            base.m_name = "CustomCE.CmdElementAttribute";   //unique id, non-localizable (e.g. "MyCategory_MyCommand")

            try
            {
                //
                // TODO: change bitmap name if necessary
                //
                string bitmapResourceName = GetType().Name + ".bmp";
                base.m_bitmap = new Bitmap(GetType(), bitmapResourceName);
            }
            catch (Exception ex)
            {
                System.Diagnostics.Trace.WriteLine(ex.Message, "Invalid Bitmap");
            }
            SymbolStyle = symbolstyle;
        }

        #region Overridden Class Methods

        /// <summary>
        /// Occurs when this command is created
        /// </summary>
        /// <param name="hook">Instance of the application</param>
        public override void OnCreate(object hook)
        {
            if (hook == null)
                return;

            if (m_hookHelper == null)
                m_hookHelper = new HookHelperClass();

            m_hookHelper.Hook = hook;

            // TODO:  Add other initialization code
        }

        /// <summary>
        /// Occurs when this command is clicked
        /// </summary>
        public override void OnClick()
        {
            // TODO: Add CmdNorthArrowAttribute.OnClick implementation

            IGraphicsContainer GraphicsContainer = m_hookHelper.ActiveView.GraphicsContainer;
            IGraphicsContainerSelect GraphicsContainerSelect = GraphicsContainer as IGraphicsContainerSelect;
            int SelectElementCount = GraphicsContainerSelect.ElementSelectionCount;
        
            IEnumElement pEnumElement = GraphicsContainerSelect.SelectedElements;
            ////�ж�ѡ��Ҫ�ص������Ƿ�����������
            IElement pElement = pEnumElement.Next();
            IElementProperties pElementProperties = pElement as IElementProperties;
            //��һ��Ҫ����������
            string pSelElementType = pElementProperties.Type;

            for (int i = 0; i < SelectElementCount ; i++)
            {
                if (pSelElementType != pElementProperties.Type)
                {
                    MessageBox.Show("��ѡ��ͬһ�����͵�Ҫ�أ�");
                    return;
                }
                pElement = pEnumElement.Next();
                pElementProperties = pElement as IElementProperties;
            }

            //��ѡ��Ҫ��������ͬʱ����ʼ�����޸���ʽ
            IEnumElement EnumElement = GraphicsContainerSelect.SelectedElements;
            EnumElement.Reset();
            IElement Element = EnumElement.Next();
            IElementProperties ElementProperties = Element as IElementProperties;           

            //��ѡ���Ҫ��Ϊָ���롢�����ߡ�ͼ����DataFrameʱ������ѡ��һ��
            if (ElementProperties.Type == "��ͼ����Ҫ�ؿ��" || ElementProperties.Type == "Map Surround Frame" || ElementProperties.Type == "Data Frame")
            {
                if (SelectElementCount == 1)
                {
                    if (ElementProperties.Name == "North Arrow")
                    {
                        LibCerMap.FrmNorthArrwoAttribute frm = new LibCerMap.FrmNorthArrwoAttribute(SymbolStyle,Element, GraphicsContainer, m_hookHelper);
                        frm.ShowDialog();
                    }
                    else if (ElementProperties.Name == "Scale Line" || ElementProperties.Name == "������" || ElementProperties.Name.Contains("Scale Bar"))
                    {
                        LibCerMap.FrmScaleBarAttribute frm = new LibCerMap.FrmScaleBarAttribute(SymbolStyle, Element, GraphicsContainer, m_hookHelper);
                        frm.ShowDialog();
                    }
                    else if (ElementProperties.Name == "Scale Text")
                    {
                        LibCerMap.FrmScaleTextAttribute frm = new LibCerMap.FrmScaleTextAttribute(SymbolStyle, Element, GraphicsContainer, m_hookHelper);
                        frm.ShowDialog();
                    }
                    else if (ElementProperties.Name == "Legend" || ElementProperties.Name == "ͼ��")
                    {
                        LibCerMap.FrmLegendAttribute frm = new LibCerMap.FrmLegendAttribute(SymbolStyle, Element, GraphicsContainer, m_hookHelper);
                        frm.ShowDialog();
                    }
                    else if (ElementProperties.Type == "Data Frame")
                    {
                        int SelIndex = 0;
                        LibCerMap.FrmFrameAttrSel frmsel = new LibCerMap.FrmFrameAttrSel();
                        frmsel.ShowDialog();
                        if (frmsel.DialogResult == DialogResult.OK)
                        {
                            SelIndex = frmsel.FrmIndex;
                        }
                        if (SelIndex == 1)
                        {
                            LibCerMap.FrmNavigationGrids frm = new LibCerMap.FrmNavigationGrids(SymbolStyle, m_hookHelper);
                            frm.ShowDialog();
                        }
                        else if (SelIndex == 2)
                        {
                            LibCerMap.FrmFrameAttribute frm = new LibCerMap.FrmFrameAttribute(SymbolStyle,Element, GraphicsContainer, m_hookHelper);
                            frm.ShowDialog();
                        }
                    }
                }
                else 
                {
                    MessageBox.Show("��ѡ��Ҫ��Ϊָ���롢�����ߡ�ͼ����Frame����ʱ��ֻ����ѡ��һ��Ҫ��");
                }
            }
            else if (ElementProperties.Type == "Text" || ElementProperties.Type == "�ı�")
            {
                LibCerMap.FrmAddText frm = new LibCerMap.FrmAddText(Element as ITextElement, m_hookHelper);
                if (frm.ShowDialog() == DialogResult.OK)
                {
                    //ITextSymbol pTextSymbol = frm.pTextElement.Symbol;
                    //for (int i = 0; i < SelectElementCount; i++)
                    //{
                    //    ITextElement pTextElement = Element as ITextElement;
                    //    //pTextElement.Symbol = pTextSymbol;
                    //    Element = EnumElement.Next();
                    //}
                    m_hookHelper.ActiveView.Refresh();
                }
            }

            else if (ElementProperties.Type == "Marker" || ElementProperties.Type == "���")
            {
                IMarkerElement pMarkerElement = Element as IMarkerElement;
                LibCerMap.FrmSymbol FrmMarker = new LibCerMap.FrmSymbol(SymbolStyle, (ISymbol)pMarkerElement.Symbol, esriSymbologyStyleClass.esriStyleClassMarkerSymbols);
                FrmMarker.ShowDialog();
                if (FrmMarker.DialogResult == DialogResult.OK)
                {
                    IMarkerSymbol pMarkerSymbol = FrmMarker.GetStyleGalleryItem().Item as IMarkerSymbol;
                    for (int i = 0; i < SelectElementCount; i++)
                    {
                        pMarkerElement.Symbol = pMarkerSymbol;
                        Element = EnumElement.Next();
                        pMarkerElement = Element as IMarkerElement;
                    }
                }
            }
            else if (ElementProperties.Type == "Line" || ElementProperties.Type == "��")
            {
                ILineElement pLineElement = Element as ILineElement;
                LibCerMap.FrmSymbol frm = new LibCerMap.FrmSymbol(SymbolStyle, (ISymbol)pLineElement.Symbol, esriSymbologyStyleClass.esriStyleClassLineSymbols);
                frm.ShowDialog();
                if (frm.DialogResult == DialogResult.OK)
                {
                    ILineSymbol pLineSymbol = frm.GetStyleGalleryItem().Item as ILineSymbol;
                    for (int i = 0; i < SelectElementCount; i++)
                    {
                        pLineElement.Symbol = pLineSymbol;
                        Element = EnumElement.Next();
                        pLineElement = Element as ILineElement;
                    }
                    
                }
            }

            else if (ElementProperties.Type == "Polygon" || ElementProperties.Type == "Rectangle" ||
                       ElementProperties.Type == "Circle" || ElementProperties.Type == "Ellipse" ||
                       ElementProperties.Type == "��" || ElementProperties.Type == "����" || 
                       ElementProperties.Type == "Բ��" || ElementProperties.Type == "��Բ")
            {
                IFillShapeElement pFillShapeElement = Element as IFillShapeElement;
                LibCerMap.FrmSymbol frm = new LibCerMap.FrmSymbol(SymbolStyle, (ISymbol)pFillShapeElement.Symbol, esriSymbologyStyleClass.esriStyleClassFillSymbols);
                frm.ShowDialog();
                if (frm.DialogResult == DialogResult.OK)
                {
                    IFillSymbol pFillsymbol = frm.GetStyleGalleryItem().Item as IFillSymbol;
                    
                    for (int i = 0; i < SelectElementCount; i++)
                    { 
                        pFillShapeElement.Symbol = pFillsymbol;
                        Element = EnumElement.Next();
                        pFillShapeElement = Element as IFillShapeElement;
                    }
                }
            }

            m_hookHelper.ActiveView.Refresh();
        }

        #endregion
    }
}
