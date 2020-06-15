#ifndef BITMAP_H
#define BITMAP_H


class MonBitmap
{
    public:
        MonBitmap() { DcBitmap = NULL; bm = NULL; Created = FALSE; }
        ~MonBitmap();
        BOOL Create( CDC * hDC, int tx, int ty );
        int * GetMemBitmap( void ) { return( MemBitmap ); }
        BOOL IsCreated( void ) { return( Created ); }
        HDC GetDC( void ) { return( DcBitmap ); }
        void Render( HDC DcDest, int PosX, int PosY, int CoeffX, int CoeffY );
        int GetTaille( void ) { return( TailleX * TailleY * 4 ); }
        int GetTailleX( void ) { return( TailleX ); }
        int GetTailleY( void ) { return( TailleY ); }
        void Clear( int Color );

    private:
        int TailleX, TailleY;
        int * MemBitmap;
        HBITMAP bm;
        HDC DcBitmap;
        BOOL Created;
};


#endif