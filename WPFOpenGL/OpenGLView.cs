using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using System.Windows.Threading;

namespace WPFOpenGL
{
    public partial class OpenGLView : UserControl,INotifyPropertyChanged
    {
        public int Interval { get; set; } = 16;
        public float R{ get => r; set => r = value; }
        public float G{ get => g; set => g = value; }
        public float B{ get => b; set => b = value; }
        public string Version { get => mVersion; set { mVersion = value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Verison")); } }
        public float ElapsedTime
        {
            get { return mElapsedTime; }
            set { if (ElapsedTime != value) { mElapsedTime = value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("ElapsedTime")); } }
        }
        public float FPS
        {
            get { return mFPS; }
            set { if (value != 0 && mFPS != 1/value) { mFPS = 1/value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("FPS")); } }
        }
        public OpenGLView()
        {
            InitializeComponent();
            windowHandler = this.Handle;
            glContext = InitOpenglContext(windowHandler);
            updateTimer.Tick += UpdateTimer_Tick;
            updateTimer.Interval = Interval;
            updateTimer.Start();
            this.Resize += OpenGLView_Resize;
            StringBuilder builder = new StringBuilder(20);
            GetString(builder,builder.Capacity);
            Version = builder.ToString();
            ClearColor(0,0.5f,1.0f);
        }
        public void SetBackgroundColor(float r, float g, float b)
        {
            if (glContext != IntPtr.Zero)
            {
                ClearColor(r,g,b);
            }
        }
        private void OpenGLView_Resize(object? sender, EventArgs e)
        {
            ResizeViewport(0, 0, this.Width, this.Height);
        }

        private void UpdateTimer_Tick(object? sender, EventArgs e)
        {
            this.Invalidate();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            stopwatch.Start();

            Clear();
            DrawTriangle(R,G,B);
            SwapWindowBuffers(this.windowHandler);

            ElapsedTime = stopwatch.Elapsed.Milliseconds;
            this.updateTimer.Interval = Interval - ElapsedTime > 0 ? (int)(Interval - ElapsedTime) : 1;

            stopwatch.Reset();
        }
        protected override void OnPaintBackground(PaintEventArgs e){}


        private IntPtr windowHandler;
        private IntPtr glContext;
        private Timer updateTimer = new Timer();
        private Stopwatch stopwatch = new Stopwatch();
        private float mElapsedTime;
        private float mFPS=60;
        private string mVersion;
        private float r=0, g=0, b=0;
        public event PropertyChangedEventHandler? PropertyChanged;


        [DllImport("OpenGLLib.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern IntPtr InitOpenglContext(IntPtr windowHandler);
        [DllImport("OpenGLLib.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern void Clear();
        [DllImport("OpenGLLib.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern void ClearColor(float r, float g, float b);
        [DllImport("OpenGLLib.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern void ResizeViewport(int startX,int startY,int width, int height);
        [DllImport("OpenGLLib.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern void SwapWindowBuffers(IntPtr windowHandler);
        [DllImport("OpenGLLib.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern void DrawTriangle(float r, float g, float b);
        [DllImport("OpenGLLib.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern void GetString(StringBuilder str,int lenght);
    }
}
