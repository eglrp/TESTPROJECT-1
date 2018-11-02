using System;
using System.Drawing;
using System.Runtime.InteropServices;
using ESRI.ArcGIS.ADF.BaseClasses;
using ESRI.ArcGIS.ADF.CATIDs;
using ESRI.ArcGIS.Controls;
using ESRI.ArcGIS.Carto;
using ESRI.ArcGIS.Geodatabase;
using ESRI.ArcGIS.Geometry;
using ESRI.ArcGIS.Display;
using LibCerMap;

namespace LibEngineCmd
{
    /// <summary>
    /// Summary description for ToolAddTinPlane.
    /// </summary>
    [Guid("9e01749b-5b8d-4028-8755-fcc8cf64c6df")]
    [ClassInterface(ClassInterfaceType.None)]
    [ProgId("CustomCE.ToolAddTinPlane")]
    public sealed class ToolAddTinPlane : BaseTool
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
        
        //Ŀ��ͼ��
        public ITinLayer pTinLayer;
        public IMap pMap;
        //��ӽڵ㴰��
        FrmAddTinPlane frmAddTINPlane = new FrmAddTinPlane();
        INewPolygonFeedback mNewPolygonFeedback = null;
        public ToolAddTinPlane()
        {
            //
            // TODO: Define values for the public properties
            //
            base.m_category = "CustomCE"; //localizable text 
            base.m_caption = "���TINƽ��";  //localizable text 
            base.m_message = "���TINƽ��";  //localizable text
            base.m_toolTip = "���TINƽ��";  //localizable text
            base.m_name = "CustomCE.ToolAddTinPlane";   //unique id, non-localizable (e.g. "MyCategory_MyTool")
            try
            {
                //
                // TODO: change resource name if necessary
                //
                string bitmapResourceName = GetType().Name + ".bmp";
                base.m_bitmap = new Bitmap(GetType(), bitmapResourceName);
                base.m_cursor = new System.Windows.Forms.Cursor(GetType(), GetType().Name + ".cur");
            }
            catch (Exception ex)
            {
                System.Diagnostics.Trace.WriteLine(ex.Message, "Invalid Bitmap");
            }
        }

        #region Overridden Class Methods

        /// <summary>
        /// Occurs when this tool is created
        /// </summary>
        /// <param name="hook">Instance of the application</param>
        public override void OnCreate(object hook)
        {
            if (hook == null)
                return;

            if (m_hookHelper == null)
                m_hookHelper = new HookHelperClass();

            m_hookHelper.Hook = hook;
            IMapControl2 pMapCtr = (((IToolbarControl)m_hookHelper.Hook).Buddy) as IMapControl2;
            if (pMapCtr != null)
            {
                pMap = pMapCtr.Map;
            }
            IPageLayoutControl pLayoutCtr = (((IToolbarControl)m_hookHelper.Hook).Buddy) as IPageLayoutControl;
            if (pLayoutCtr != null)
            {
                pMap = pLayoutCtr.ActiveView.FocusMap;
            }
            frmAddTINPlane.Owner =
                   System.Windows.Forms.Form.FromChildHandle(User32API.GetCurrentWindowHandle()) as System.Windows.Forms.Form;

            // TODO:  Add ToolAddTinPlane.OnCreate implementation
        }


        public override bool Enabled
        {
            get
            {
                // TODO: Add CmdNorthArrow.OnClick implementation   
                IMapControl2 pMapCtr = (((IToolbarControl)m_hookHelper.Hook).Buddy) as IMapControl2;
                if (pMapCtr == null)
                {
                    return false;
                }
                if (pTinLayer == null)
                {
                    return false;
                }
                else
                {
                    ITin pTin = pTinLayer.Dataset;
                    ITinEdit pTinEdit = pTin as ITinEdit;
                    return pTinEdit.IsInEditMode;
                }
            }
        }

        /// <summary>
        /// Occurs when this tool is clicked
        /// </summary>
        public override void OnClick()
        {
            // TODO: Add ToolAddTinPlane.OnClick implementation   
            frmAddTINPlane.Show();
        }

        public override void OnMouseDown(int Button, int Shift, int X, int Y)
        {
            // TODO:  Add ToolAddTinPlane.OnMouseDown implementation
            frmAddTINPlane.setButtonOkEnable(false);
            IMapControl2 pMapCtr = (((IToolbarControl)m_hookHelper.Hook).Buddy) as IMapControl2;            
            if (pMapCtr != null)
            { 
                IPoint mapPoint = pMapCtr.ToMapPoint(X, Y);
                if (mNewPolygonFeedback == null)
                {
                    mNewPolygonFeedback = new NewPolygonFeedbackClass();
                    mNewPolygonFeedback.Display = pMapCtr.ActiveView.ScreenDisplay;
                    mNewPolygonFeedback.Start(mapPoint);                   
                }
                else
                {
                    mapPoint = pMapCtr.ToMapPoint(X, Y);
                    mNewPolygonFeedback.AddPoint(mapPoint);
                }                        
            }           
        }

        public override void OnMouseMove(int Button, int Shift, int X, int Y)
        {
            // TODO:  Add ToolAddTinPlane.OnMouseMove implementation
            IMapControl2 pMapCtr = (((IToolbarControl)m_hookHelper.Hook).Buddy) as IMapControl2;
            if (mNewPolygonFeedback != null && pMapCtr != null)
            {
                IPoint mapPoint = pMapCtr.ToMapPoint(X, Y);
                mNewPolygonFeedback.MoveTo(mapPoint);
            }
             
        }

        public override void OnMouseUp(int Button, int Shift, int X, int Y)
        {
            // TODO:  Add ToolAddTinPlane.OnMouseUp implementation
        }
        public override void OnDblClick()
        {
            base.OnDblClick();
            ITin pTin = pTinLayer.Dataset;
            ITinEdit pTinEdit = pTin as ITinEdit;
            frmAddTINPlane.pTinEdit = pTinEdit;
            if (mNewPolygonFeedback != null)
            {
                IPolygon polygon = mNewPolygonFeedback.Stop();
                frmAddTINPlane.pGeometry = polygon;
                frmAddTINPlane.setButtonOkEnable(true);
                frmAddTINPlane.CalPlaneHeight();
                IMapControl2 pMapCtr = (((IToolbarControl)m_hookHelper.Hook).Buddy) as IMapControl2;
                frmAddTINPlane.pMapCtr = pMapCtr;
                mNewPolygonFeedback = null;
            }
        }
        public override bool Deactivate()
        {
            frmAddTINPlane.Hide();
            frmAddTINPlane.setButtonOkEnable(false);
            mNewPolygonFeedback = null;
            return base.Deactivate();
        }
        #endregion
    }
}
