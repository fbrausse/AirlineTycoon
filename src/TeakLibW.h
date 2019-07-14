#pragma once

typedef UWORD word;
typedef ULONG dword;

extern void memswap(void* param_1, void* param_2, ULONG param_3);
extern char* bprintf(char const*, ...);
extern char* bitoa(long, long = 10);
extern void here(char*, long);

extern const char* ExcAssert;
extern const char* ExcGuardian;
extern const char* ExcImpossible;
extern const char* ExcNotImplemented;
extern const char* ExcOutOfMem;
extern const char* ExcStrangeMem;

#define FNL 0, 0

extern long TeakLibW_Exception(char* param_1, long param_2, const char* param_3, ...);
extern char* TeakStrRemoveEndingCodes(char*, char const*);
extern unsigned char GerToLower(unsigned char);
extern unsigned char GerToUpper(unsigned char);
extern unsigned char* RecapizalizeString(unsigned char*);

template <typename T>
class BUFFER
{
public:
    BUFFER(SLONG anz)
    {
        if (anz == 0)
        {
            MemPointer = MemBufferUsed = NULL;
        }
        else
        {
            MemPointer = MemBufferUsed = new T[anz]();
            if (!MemPointer)
                TeakLibW_Exception(NULL, 0, ExcOutOfMem);
        }

        Size = anz;
    }

    BUFFER(void) : MemPointer(0), MemBufferUsed(0), Size(0) {}

    ~BUFFER()
    {
        delete[] MemPointer;
    }

    void ReSize(SLONG anz)
    {
        if (anz == 0)
        {
            if (!MemPointer)
                delete[] MemPointer;

            MemPointer = MemBufferUsed = NULL;
        }

        T* m = new T[anz]();
        if (!m)
            TeakLibW_Exception(NULL, 0, ExcOutOfMem);

        if (!MemPointer)
        {
            MemBufferUsed = m;
        }
        else
        {
            SLONG num;
            if (anz < Size) {
                num = anz;
            }
            else {
                num = Size;
            }

            memswap(m, MemPointer, sizeof(T) * num);
            delete[] MemPointer;

            MemBufferUsed = m + ((MemBufferUsed - MemPointer) / sizeof(T));
        }

        MemPointer = m;
        Size = anz;
    }

    void ReSize(SLONG, T*)
    {
        DebugBreak();
    }

    long AnzEntries() const { return Size; }

    void FillWith(T value)
    {
        for (int i = 0; i < Size; i++)
            MemPointer[i] = value;
        MemBufferUsed = MemPointer + Size;
    }

    //T& operator[](int i) const
    //{
    //    return MemPointer[i];
    //}

    operator T* ()
    {
        return MemPointer;
    }

    operator const T* () const
    {
        return MemPointer;
    }

    void operator+=(T& rhs)
    {
        DebugBreak();
        *MemBufferUsed++ = rhs;
    }

    void operator+=(int rhs)
    {
        DebugBreak();
        *MemBufferUsed++ = (T)rhs;
    }

    T* MemPointer;
    T* DelPointer;
    T* MemBufferUsed;
    SLONG Size;
};

#define TEAKFILE_READ	1
#define TEAKFILE_WRITE	2

class TEAKFILE
{
public:
    TEAKFILE(void);
    TEAKFILE(char const*, long);
    ~TEAKFILE(void);

    void ReadLine(char*, long);
    int IsEof(void);
    void Close(void);
    long GetFileLength(void);
    long GetPosition(void);
    void Open(char const*, long);
    int IsOpen(void);
    unsigned char* Read(long);
    void Read(unsigned char*, long);
    char* ReadLine(void);
    void ReadTrap(long);
    void WriteTrap(long);
    void SetPasswort(char*);
    void SetPosition(long);
    void Skip(long);
    void Write(unsigned char*, long);
    void WriteLine(char*);
    void Announce(long);

    void* MemPointer;
    ULONG MemBufferUsed;
    BUFFER<UBYTE> MemBuffer;

    friend TEAKFILE& operator << (TEAKFILE& File, const BOOL& b) { File.Write((UBYTE*)& b, sizeof(b)); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, BOOL& b) { File.Read((UBYTE*)& b, sizeof(b)); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const UBYTE& b) { File.Write((UBYTE*)& b, sizeof(b)); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, UBYTE& b) { File.Read((UBYTE*)& b, sizeof(b)); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const SBYTE& b) { File.Write((UBYTE*)& b, sizeof(b)); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, SBYTE& b) { File.Read((UBYTE*)& b, sizeof(b)); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const UWORD& b) { File.Write((UBYTE*)& b, sizeof(b)); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, UWORD& b) { File.Read((UBYTE*)& b, sizeof(b)); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const SWORD& b) { File.Write((UBYTE*)& b, sizeof(b)); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, SWORD& b) { File.Read((UBYTE*)& b, sizeof(b)); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const ULONG& b) { File.Write((UBYTE*)& b, sizeof(b)); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, ULONG& b) { File.Read((UBYTE*)& b, sizeof(b)); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const SLONG& b) { File.Write((UBYTE*)& b, sizeof(b)); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, SLONG& b) { File.Read((UBYTE*)& b, sizeof(b)); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const __int64& b) { File.Write((UBYTE*)& b, sizeof(b)); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, __int64& b) { File.Read((UBYTE*)& b, sizeof(b)); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const double& b) { File.Write((UBYTE*)& b, sizeof(b)); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, double& b) { File.Read((UBYTE*)& b, sizeof(b)); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const float& b) { File.Write((UBYTE*)& b, sizeof(b)); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, float& b) { File.Read((UBYTE*)& b, sizeof(b)); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const CString& b) { DebugBreak(); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, CString& b) { DebugBreak(); return File; }

    friend TEAKFILE& operator << (TEAKFILE& File, const CPoint& b) { DebugBreak(); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, CPoint& b) { DebugBreak(); return File; }

private:
    void CodeBlock(unsigned char*, long, long);
};

template <typename T>
class FBUFFER : public BUFFER<T>
{
public:
    FBUFFER(void) : BUFFER<T>(0) {}

    FBUFFER(SLONG anz) : BUFFER<T>(anz) {}

    friend TEAKFILE& operator << (TEAKFILE& File, const FBUFFER<T>& buffer) { DebugBreak(); return File; }
    friend TEAKFILE& operator >> (TEAKFILE& File, FBUFFER<T>& buffer) { DebugBreak(); return File; }
};

class TEAKRAND
{
public:
    TEAKRAND(void);
    TEAKRAND(ULONG _Seed);

    void SRand(ULONG _Seed);
    void SRandTime(void);
    void Reset(void);

    UWORD Rand(void);
    UWORD Rand(SLONG Max);
    UWORD Rand(SLONG Min, SLONG Max);
    ULONG GetSeed(void);

    friend TEAKFILE& operator << (TEAKFILE& File, const TEAKRAND& r);
    friend TEAKFILE& operator >> (TEAKFILE& File, TEAKRAND& r);

private:
    ULONG Seed;
    ULONG Value;
};

template <typename T>
class TXY
{
public:
    T x, y;

    TXY() : x(), y() {}
    TXY(T s) : x(s), y(s) {}
    TXY(T x, T y) : x(x), y(y) {}
    TXY(POINT& point) : x(point.x), y(point.y) {}

    TXY operator+(const TXY& b) const
    {
        return TXY(x + b.x, y + b.y);
    }

    TXY operator-(const TXY& b) const
    {
        return TXY(x - b.x, y - b.y);
    }

    TXY operator*(const TXY& b) const
    {
        return TXY(x * b.x, y * b.y);
    }

    TXY operator/(const TXY& b) const
    {
        return TXY(x / b.x, y / b.y);
    }

    T operator*(const T& b) const
    {
        DebugBreak();
        return 0;
    }

    T operator/(const T& b) const
    {
        DebugBreak();
        return 0;
    }

    TXY operator-() const
    {
        return TXY(-x, -y);
    }

    bool operator==(const TXY& b) const
    {
        return x == b.x
            && y == b.y;
    }

    bool operator!=(const TXY& b) const
    {
        return x != b.x
            && y != b.y;
    }

    bool operator<(const TXY& b) const
    {
        return x < b.x
            && y < b.y;
    }

    bool operator>(const TXY& b) const
    {
        return x > b.x
            && y > b.y;
    }

    TXY& operator-=(const TXY& b)
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }

    TXY& operator+=(const TXY& b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }

    TXY& operator/=(const TXY& b)
    {
        x /= b.x;
        y /= b.y;
        return *this;
    }

    TXY& operator*=(const TXY& b)
    {
        x *= b.x;
        y *= b.y;
        return *this;
    }

    operator POINT& ()
    {
        return reinterpret_cast<POINT&>(*this);
    }

    operator CPoint& ()
    {
        return reinterpret_cast<CPoint&>(*this);
    }

    T abs() const
    {
        DebugBreak();
        return 0;
    }

    bool IfIsWithin(T _x, T _y, T w, T h) const
    {
        DebugBreak();
        return x >= _x && y >= _y && x <= _x + w && y <= _y + h;
    }

    bool IfIsWithin(T a, T b, T c) const
    {
        DebugBreak();
        return false;
    }

    bool IfIsWithin(const TXY<T>& a, const TXY<T>& b) const
    {
        DebugBreak();
        return a < *this && *this < b;
    }

    friend TEAKFILE& operator << (TEAKFILE& File, const TXY<T>& b) { File.Write((UBYTE*)& b, sizeof(T) * 2); return (File); }
    friend TEAKFILE& operator >> (TEAKFILE& File, TXY<T>& b) { File.Read((UBYTE*)& b, sizeof(T) * 2); return (File); }
};

template <typename T>
class TXYZ
{
public:
    T x, y, z;

    TXYZ() : x(), y(), z() {}
    TXYZ(T s) : x(s), y(s), z(s) {}
    TXYZ(T x, T y, T z) : x(x), y(y), z(z) {}

    TXYZ operator+(const TXYZ& b) const
    {
        return TXY(x + b.x, y + b.y, z + b.z);
    }

    TXYZ operator-(const TXYZ& b) const
    {
        return TXY(x - b.x, y - b.y, z - b.z);
    }

    TXYZ operator*(const TXYZ& b) const
    {
        return TXY(x * b.x, y * b.y, z * b.z);
    }

    TXYZ operator/(const TXYZ& b) const
    {
        return TXY(x / b.x, y / b.y, z / b.z);
    }

    TXYZ operator*(const T& b) const
    {
        return TXY(x * b, y * b, z * b);
    }

    TXYZ operator/(const T& b) const
    {
        return TXY(x / b, y / b, z / b);
    }

    TXYZ operator-() const
    {
        return TXY(-x, -y, -z);
    }

    bool operator==(const TXYZ& b) const
    {
        return x == b.x
            && y == b.y
            && z == b.z;
    }

    bool operator!=(const TXYZ& b) const
    {
        return x != b.x
            && y != b.y
            && z != b.z;
    }

    bool operator<(const TXYZ& b) const
    {
        return x < b.x
            && y < b.y
            && z < b.z;
    }

    bool operator>(const TXYZ& b) const
    {
        return x > b.x
            && y > b.y
            && z > b.z;
    }

    TXYZ& operator-=(const TXYZ& b)
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }

    TXYZ& operator+=(const TXYZ& b)
    {
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }

    TXYZ& operator/=(const TXYZ& b)
    {
        x /= b.x;
        y /= b.y;
        z /= b.z;
        return *this;
    }

    TXYZ& operator*=(const TXYZ& b)
    {
        x *= b.x;
        y *= b.y;
        z *= b.z;
        return *this;
    }

    T abs() const
    {
        DebugBreak();
        return 0;
    }

    friend TEAKFILE& operator << (TEAKFILE& File, const TXYZ<T>& b) { File.Write((UBYTE*)& b, sizeof(T) * 3); return (File); }
    friend TEAKFILE& operator >> (TEAKFILE& File, TXYZ<T>& b) { File.Read((UBYTE*)& b, sizeof(T) * 3); return (File); }
};

typedef TXY<SLONG> XY;
typedef TXYZ<SLONG> XYZ;

typedef TXY<FLOAT> FXY;
typedef TXYZ<FLOAT> FXYZ;

class PALETTE
{
public:
    PALETTE(void);
    PALETTE(IDirectDraw*, CString const&);

    void Blend(long, long) const;
    void BlendIn(void) const;
    void BlendOut(void) const;
    void RefreshDD(int) const;
    void RefreshDD(long, int) const;
    void RefreshPal(IDirectDraw*, CString const&);
    void RefreshPalFromLbm(CString const&);
    void RefreshPalFromPcx(CString const&);
    void ConvertToBlackWhite(void);
    unsigned char FindColorClosestToRGB(unsigned char, unsigned char, unsigned char) const;
    void RotateArea(long, long);
    void CopyArea(long, long, long);
    void CopyAreaFrom(PALETTE const&, long, long, long);

    BUFFER<PALETTEENTRY> Pal;
};

#define TEXTRES_CACHED (void*)1

class TEXTRES
{
public:
    TEXTRES() {};
    TEXTRES(char const*, void*);
    ~TEXTRES(void);

    void Open(char const*, void*);
    BUFFER<char>& GetB(unsigned long, unsigned long);
    char* GetP(unsigned long, unsigned long);
    char* GetS(unsigned long, unsigned long);
    char* GetS(unsigned long, char const*);
    char* GetS(char const* c, unsigned long i) { return GetS(i, c); }
};

class CRegistration
{
public:
    CRegistration(void);
    CRegistration(CString const&, unsigned long);
    void ReSize(CString const&, unsigned long);
    CString GetDisplayString(void);
    long GetMode(void);
    CString GetSomeString(char*);
    unsigned long CalcChecksum(CString);
    int IsMaster(void);
    void CheckIfIsMaster(void);
};

#define VIDRAMBM 1
#define SYSRAMBM 2

class TECBM
{
public:
    TECBM(void);
    TECBM(CString const&, void* = NULL);
    TECBM(CString const&, long, void* = NULL);
    TECBM(long, long, void*);
    TECBM(TXY<long>, void*);
    ~TECBM(void);

    void Destroy(void);
    TECBM& operator=(TECBM&);
    virtual int Refresh(void);
    int TextOutA(long, long, unsigned long, unsigned long, CString const&);
    int IsOk(void) const;
    static int IsMemCritical(void);
    static int IsHardwareCritical(void);
    static int IsEitherCritical(void);
    static void SetCriticalMem(long);
    void ReSize(CString const&, void* = NULL);
    void ReSize(CString const&, long, void* = NULL);
    void ReSizeLbm(CString const&, void* = NULL);
    void ReSizeLbm(CString const&, long, void* = NULL);
    void ReSize(TXY<long>, void* = NULL);
    void ReSizePcx(CString const&, long, void* = NULL);
    void ReSizePcx(CString const&, void* = NULL);
    int SavePCX(CString const&, PALETTE const&) const;
    void ShiftColors(long);
    void RemapColor(unsigned char, unsigned char);
    int BlitFrom(TECBM const&, TXY<long>, TXY<long>);
    int BlitFromT(TECBM const&, TXY<long>, TXY<long>, unsigned char);
    void InterleaveBitmaps(TECBM const&, TECBM const&, long);
    int UniversalClip(TXY<long>*, CRect*);
    void GetClipRegion(TXY<long>*, TXY<long>*);
    void SetClipRegion(void);
    void SetClipRegion(TXY<long>, TXY<long>);
    int IsLost(void) const;
    int SetPixel(TXY<long>, unsigned char);
    unsigned char GetPixel(TXY<long>) const;
    int FillWith(unsigned char);
    int FillWith(TECBM const&);
    int FillWith(TECBM const&, TXY<long>);
    int Line(TXY<long> const&, TXY<long> const&, unsigned char);
    int HLine(long, long, long, unsigned char);
    int VLine(long, long, long, unsigned char);
    int DotLine(TXY<long> const&, TXY<long> const&, unsigned char);
    int Rectangle(TXY<long> const&, TXY<long> const&, unsigned char);
    int Box(TXY<long>, TXY<long>, unsigned char);
    int Box(TXY<long> const&, TXY<long> const&, TECBM const&);
    int Box(TXY<long> const&, TXY<long> const&, TECBM const&, TXY<long>);
    int Circle(TXY<long> const&, long, unsigned char);
    int BlitFrom(TECBM&, TXY<long>);
    int BlitFromT(TECBM&, TXY<long>);
    int BlitPartFrom(TECBM&, TXY<long>, TXY<long> const&, TXY<long> const&);
    int BlitPartFromT(TECBM&, TXY<long>, TXY<long> const&, TXY<long> const&);
    long GetAnzSubBitmaps(void) const;
    TECBM* ParseNextVertikalSubBitmap(void);
    TECBM* ParseNextHorizontalSubBitmap(void);
    FBUFFER<TECBM>* ParseVertikalSubBitmaps(void);
    void ParseHorizontalSubBitmapsInto(FBUFFER<TECBM>&);
    FBUFFER<TECBM>* ParseHorizontalSubBitmaps(void);
    TECBM* ParseVertikalSubBitmapNumberX(long);
    TECBM* ParseHorizontalSubBitmapNumberX(long);
    int ParseVertikalSubBitmapNumberXInto(long, TECBM&);
    int ParseHorizontalSubBitmapNumberXInto(long, TECBM&);

    XY Size;

private:
    static bool BltSupport;
    static long CriticalVidMem;
    static long TotalVidMem;
};

class TECBMKEY
{
public:
    TECBMKEY(TECBM&);
    ~TECBMKEY(void);

    UBYTE* Bitmap;
};

class TECBMKEYC
{
public:
    TECBMKEYC(const TECBM&);
    ~TECBMKEYC(void);

    long lPitch;
    const UBYTE* Bitmap;
};


class HDU
{
public:
    HDU();
    ~HDU();

    void Close();
    void Disable();
    void ClearScreen();
    void HercPrintf(int, char* Format, ...);
    void HercPrintf(char* Format, ...);
    void LogPosition(const char*, int);
};

extern HDU Hdu;

#define hprintf Hdu.HercPrintf
#define hprintvar(x) Hdu.HercPrintf("%d\n", x)

class XID
{
public:
    XID(void);
    void SetValue(unsigned long);

    friend TEAKFILE& operator<<(TEAKFILE&, XID const&);
    friend TEAKFILE& operator>>(TEAKFILE&, XID&);
};

extern void TeakAlbumRemoveT(FBUFFER<unsigned long>&, unsigned long, CString const&, unsigned long);
extern void TeakAlbumRefresh(FBUFFER<unsigned long>&, unsigned long);
extern long TeakAlbumSearchT(FBUFFER<unsigned long>&, unsigned long, CString const&, unsigned long);
extern long TeakAlbumXIdSearchT(FBUFFER<unsigned long>&, unsigned long, CString const&, XID&);
extern bool TeakAlbumIsInAlbum(FBUFFER<unsigned long>&, unsigned long, unsigned long);
extern unsigned long TeakAlbumAddT(FBUFFER<unsigned long>&, unsigned long, CString const&, unsigned long);
extern unsigned long TeakAlbumFrontAddT(FBUFFER<unsigned long>&, unsigned long, CString const&, unsigned long);
extern unsigned long TeakAlbumGetNumFree(FBUFFER<unsigned long>&, unsigned long);
extern unsigned long TeakAlbumGetNumUsed(FBUFFER<unsigned long>&, unsigned long);
extern unsigned long TeakAlbumRandom(FBUFFER<unsigned long>&, unsigned long, CString const&, TEAKRAND*);

template <typename T>
class ALBUM
{
public:
    ALBUM(BUFFER<T>& buffer, CString str)
        : values(reinterpret_cast<FBUFFER<T>&>(buffer))
        , name(str)
    {
        //TeakAlbumRefresh(ids, values.AnzEntries());
    }

    void Repair(BUFFER<T>& buffer)
    {
        DebugBreak();
    }

    bool IsInAlbum(unsigned long id)
    {
        DebugBreak();
        //return TeakAlbumIsInAlbum(ids, values.AnzEntries(), id);
        return 0;
    }

    long AnzEntries()
    {
        return values.AnzEntries();
    }

    long GetNumFree()
    {
        DebugBreak();
        //return TeakAlbumGetNumFree(ids, values.AnzEntries());
        return 0;
    }

    long GetNumUsed()
    {
        DebugBreak();
        //return TeakAlbumGetNumUsed(ids, values.AnzEntries());
        return 0;
    }

    long GetRandomUsedIndex(TEAKRAND* rand = NULL)
    {
        DebugBreak();
        //return TeakAlbumRandom(ids, values.AnzEntries(), name, rand);
        return 0;
    }

    long GetUniqueId()
    {
        DebugBreak();
        return 0;
    }

    unsigned long GetIdFromIndex(long i)
    {
        DebugBreak();
        return ids[i];
    }

    void ClearAlbum()
    {
        DebugBreak();
        //TeakAlbumRefresh(ids, values.AnzEntries());
        for (long i = ids.AnzEntries() - 1; i >= 0; --i)
            ids[i] = 0;
    }

    void Swap(long a, long b)
    {
        DebugBreak();
    }

    void ResetNextId()
    {
        DebugBreak();
        NextId = 0;
    }

    void Sort()
    {
        DebugBreak();
    }

    unsigned long operator*=(unsigned long id)
    {
        DebugBreak();
        //return TeakAlbumFrontAddT(ids, values.AnzEntries(), name, id);
        return 0;
    }

    unsigned long operator+=(unsigned long id)
    {
        DebugBreak();
        //return TeakAlbumAddT(ids, values.AnzEntries(), name, id);
        return 0;
    }

    void operator-=(unsigned long id)
    {
        DebugBreak();
        //TeakAlbumRemoveT(ids, values.AnzEntries(), name, id);
    }

    unsigned long operator*=(T& rhs)
    {
        DebugBreak();
        //return TeakAlbumFrontAddT(ids, values.AnzEntries(), name, 0);
        return 0;
    }

    unsigned long operator+=(T& rhs)
    {
        DebugBreak();
        //return TeakAlbumAddT(ids, values.AnzEntries(), name, 0);
        return 0;
    }

    void operator-=(T& rhs)
    {
        DebugBreak();
        //TeakAlbumRemoveT(ids, values.AnzEntries(), name, 0);
    }

    long operator()(unsigned long id)
    {
        DebugBreak();
        //return TeakAlbumSearchT(ids, values.AnzEntries(), name, id);
        return 0;
    }

    T& operator[](unsigned long i)
    {
        DebugBreak();
        return values[i];
    }

    friend TEAKFILE& operator<< (TEAKFILE& File, const ALBUM<T>& r) { DebugBreak(); return File; }
    friend TEAKFILE& operator>> (TEAKFILE& File, ALBUM<T>& r) { DebugBreak(); return File; }

private:
    FBUFFER<unsigned long> ids;
    FBUFFER<T>& values;
    CString name;
    unsigned long NextId;
};

extern int DoesFileExist(char const*);
extern void LoadCompleteFile(char const*, unsigned char*);
extern BUFFER<unsigned char>* LoadCompleteFile(char const*);
extern long CalcInertiaVelocity(long, long);
extern long Calc1nSum(long);

template <class T>
inline void Limit(T min, T& value, T max)
{
    if (value < min) value = min;
    if (value > max) value = max;
}

template <class T>
inline void Swap(T& a, T& b)
{
    T c(a);
    a = b;
    b = c;
}

template <class T>
inline const T& Min(const T& a, const T& b)
{
    return (b < a) ? b : a;
}


template <class T>
inline const T& Max(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

inline ReferTo(...) {}

inline MB() {}
