using OpenCV.Net;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Bonsai.Tld
{
    class BoxContour : Contour
    {
        const uint CV_MAGIC_MASK = 0xFFFF0000;
        const uint CV_SEQ_MAGIC_VAL = 0x42990000;
        static readonly int PointSize = Marshal.SizeOf(typeof(Point));
        static readonly int SeqBlockSize = Marshal.SizeOf(typeof(_CvSeqBlock));
        static readonly new int HeaderSize = Contour.HeaderSize + SeqBlockSize + PointSize * 4;

        public BoxContour(Rect rect)
        {
            unsafe
            {
                var ptr = Marshal.AllocHGlobal(HeaderSize);
                var points = (int*)((byte*)ptr + Contour.HeaderSize + SeqBlockSize);
                points[0] = rect.X;
                points[1] = rect.Y;
                points[2] = rect.X + rect.Width;
                points[3] = rect.Y;
                points[4] = rect.X + rect.Width;
                points[5] = rect.Y + rect.Height;
                points[6] = rect.X;
                points[7] = rect.Y + rect.Height;

                var seqBlock = (_CvSeqBlock*)((byte*)ptr + Contour.HeaderSize);
                seqBlock->start_index = 0;
                seqBlock->count = 4;
                seqBlock->data = (IntPtr)points;
                seqBlock->next = (IntPtr)seqBlock;
                seqBlock->prev = (IntPtr)seqBlock;

                var contour = (_CvContour*)ptr;
                var seqFlags = (int)SequenceElementType.Point | (int)SequenceKind.Curve | (int)SequenceFlags.Closed;
                contour->flags = (int)((seqFlags & ~CV_MAGIC_MASK) | CV_SEQ_MAGIC_VAL);
                contour->header_size = Contour.HeaderSize;
                contour->h_next = IntPtr.Zero;
                contour->h_prev = IntPtr.Zero;
                contour->v_next = IntPtr.Zero;
                contour->v_prev = IntPtr.Zero;
                contour->total = 4;
                contour->elem_size = Marshal.SizeOf(typeof(Point));
                contour->block_max = (IntPtr)((byte*)ptr + HeaderSize);
                contour->ptr = contour->block_max;
                contour->delta_elems = 128;
                contour->storage = IntPtr.Zero;
                contour->free_blocks = IntPtr.Zero;
                contour->first = (IntPtr)seqBlock;
                contour->color = 0;
                contour->rect = rect;
                contour->reserved0 = 0;
                contour->reserved1 = 0;
                contour->reserved2 = 0;
                SetHandle(ptr);
            }
        }

        protected override bool ReleaseHandle()
        {
            Marshal.FreeHGlobal(handle);
            return true;
        }

        [StructLayout(LayoutKind.Sequential)]
        struct _CvSeqBlock
        {
            public IntPtr prev;
            public IntPtr next;
            public int start_index;
            public int count;
            public IntPtr data;
        };

        [StructLayout(LayoutKind.Sequential)]
        struct _CvContour
        {
            public int flags;
            public int header_size;
            public IntPtr h_prev;
            public IntPtr h_next;
            public IntPtr v_prev;
            public IntPtr v_next;
            public int total;
            public int elem_size;
            public IntPtr block_max;
            public IntPtr ptr;
            public int delta_elems;
            public IntPtr storage;
            public IntPtr free_blocks;
            public IntPtr first;

            public Rect rect;
            public int color;
            public int reserved0;
            public int reserved1;
            public int reserved2;
        }
    }
}
