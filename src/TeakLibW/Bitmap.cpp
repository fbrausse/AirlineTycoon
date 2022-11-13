#include "stdafx.h"
#include <SDL_image.h>

const char* ExcPrimarySurface   = "CreatePrimarySurface failed";
const char* ExcAttachSurface    = "GetAttachedSurface failed";
const char* ExcBackbuffer       = "Create Backbuffer failed";
const char* ExcReresize         = "Can't reresize TECPRIMARYBM";
const char* ExcAttachPal        = "Can't attach Palette";
const char* ExcNotPcx           = "%s is not a valid pcx-file!";
const char* ExcNotLbm           = "%s is not a valid lbm-file!";
const char* ExcNotTga           = "%s is not a valid tga-file!";
const char* ExcPicUnknown       = "%s is not a known picture file!";

XYZ DetectCurrentDisplayResolution()
{
    SDL_DisplayMode current;

    if (SDL_GetCurrentDisplayMode(0, &current) != 0)
        TeakLibW_Exception(0, 0, ExcPrimarySurface);

    return XYZ(current.w, current.h, SDL_BITSPERPIXEL(current.format));
}

TECBM::TECBM()
    : Surface(NULL)
    , Size(0,0)
{
}

TECBM::TECBM(CString const& path, void* flags)
    : Surface(NULL)
    , Size(0,0)
{
    ReSize(path, flags);
}

TECBM::TECBM(const char *lbm, const char *pcx, const char *tga, void *flags)
    : Surface(NULL)
    , Size(0,0)
{
    ReSize(lbm, pcx, tga, flags);
}

TECBM::~TECBM()
{
    if (Surface)
        SDL_FreeSurface(Surface);
}

int TECBM::Refresh()
{
    TeakLibW_Exception(0, 0, ExcNotImplemented);
    return 0;
}

static SDL_Surface * load_one_of(const char *lbm, const char *pcx, const char *tga)
{
    static const struct {
        decltype(IMG_isLBM) *is;
        decltype(IMG_LoadLBM_RW) *load;
        const char *exc;
    } fmts[3] = {
        { IMG_isLBM, IMG_LoadLBM_RW, ExcNotLbm },
        { IMG_isPCX, IMG_LoadPCX_RW, ExcNotPcx },
        { NULL     , IMG_LoadTGA_RW, ExcNotTga },
    };

    const char *paths[] = { lbm, pcx, tga };

    int any = -1;
    for (size_t i=0; i<sizeof(paths)/sizeof(*paths); i++) {
        if (!paths[i])
            continue;
        any = i;
        SDL_RWops* file = SDL_RWFromFile(paths[i], "rb");
        if (!file)
            continue;
        bool ok = false;
        SDL_Surface *surface = NULL;
        if (!fmts[i].is || fmts[i].is(file))
            surface = fmts[i].load(file);
        SDL_RWclose(file);
        if (surface)
            return surface;
    }
    if (any != -1)
        TeakLibW_Exception(0, 0, fmts[any].exc, paths[any]);
    return NULL;
}

void TECBM::ReSize(const char *lbm, const char *pcx, const char *tga, void* flags)
{
    if ((Surface = load_one_of(lbm, pcx, tga))) {
        Size.x = Surface->w;
        Size.y = Surface->h;
    }
}

void TECBM::ReSize(CString const& path, void* flags)
{
    const char* suffix = GetSuffix(path);
    if (!stricmp(suffix, "lbm") || !stricmp(suffix, "bbm"))
        ReSizeLbm(path, flags);
    else if (!stricmp(suffix, "pcx") || !stricmp(suffix, "pcc"))
        ReSizePcx(path, flags);
    else
        TeakLibW_Exception(0, 0, ExcPicUnknown, path);
}

void TECBM::ReSizeLbm(CString const& path, void* flags)
{
    ReSize(path, NULL, NULL, flags);
}

void TECBM::ReSizePcx(CString const& path, void* flags)
{
    ReSize(NULL, path, NULL, flags);
}

TECBMKEY::TECBMKEY(TECBM& bm)
    : Surface(bm.Surface)
    , Bitmap((UBYTE*)bm.Surface->pixels)
    , lPitch(bm.Surface->pitch)
{
    if (SDL_LockSurface(Surface) != 0)
        TeakLibW_Exception(0, 0, ExcAttachSurface);
}

TECBMKEY::~TECBMKEY(void)
{
    SDL_UnlockSurface(Surface);
}

TECBMKEYC::TECBMKEYC(const TECBM& bm)
    : Surface(bm.Surface)
    , Bitmap((const UBYTE*)bm.Surface->pixels)
    , lPitch(bm.Surface->pitch)
{
    if (SDL_LockSurface(Surface) != 0)
        TeakLibW_Exception(0, 0, ExcAttachSurface);
}

TECBMKEYC::~TECBMKEYC(void)
{
    SDL_UnlockSurface(Surface);
}

PALETTE::PALETTE()
{
}

void PALETTE::RefreshPalFrom(const char *lbm, const char *pcx, const char *tga)
{
    if (SDL_Surface *surface = load_one_of(lbm, pcx, tga)) {
        SDL_Palette* palette = surface->format->palette;
        Pal.ReSize(palette->ncolors);
        for (int i = 0; i < palette->ncolors; ++i)
            Pal[i] = (palette->colors)[i];
        SDL_FreeSurface(surface);
    }
}

void PALETTE::RefreshPalFromLbm(CString const& path)
{
    RefreshPalFrom(path, NULL, NULL);
}

void PALETTE::RefreshPalFromPcx(CString const& path)
{
    RefreshPalFrom(NULL, path, NULL);
}

void PALETTE::RefreshPalFromTga(CString const& path)
{
    RefreshPalFrom(NULL, NULL, path);
}
