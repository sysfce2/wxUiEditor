#ifndef DISABLED_PNG_H
#define DISABLED_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char disabled_png[] =
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 
	0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 
	0xF3, 0xFF, 0x61, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 
	0x73, 0x00, 0x00, 0x0B, 0x13, 0x00, 0x00, 0x0B, 0x13, 0x01, 
	0x00, 0x9A, 0x9C, 0x18, 0x00, 0x00, 0x01, 0x67, 0x49, 0x44, 
	0x41, 0x54, 0x38, 0xCB, 0x95, 0x53, 0x31, 0x6E, 0xC2, 0x40, 
	0x10, 0x9C, 0xB5, 0x8D, 0x44, 0x9A, 0x70, 0x4A, 0x44, 0x11, 
	0x28, 0x70, 0xC1, 0x0F, 0x82, 0xD2, 0xF1, 0x01, 0x3A, 0xF7, 
	0x94, 0x54, 0xB4, 0xD4, 0x14, 0x14, 0x29, 0x69, 0xF2, 0x04, 
	0xE4, 0x82, 0x82, 0x3A, 0x2F, 0xA0, 0x8A, 0x4E, 0x3C, 0x20, 
	0x52, 0x44, 0x13, 0x19, 0x29, 0x20, 0x64, 0x53, 0x60, 0x27, 
	0xD8, 0xDE, 0x14, 0xC1, 0x27, 0x1B, 0x6C, 0x22, 0xA6, 0xBA, 
	0x3B, 0xCD, 0xCC, 0xED, 0xCE, 0xDD, 0x12, 0x8E, 0x78, 0xEA, 
	0xF5, 0x98, 0x34, 0x0D, 0x37, 0x42, 0x24, 0x47, 0x38, 0xF8, 
	0x3E, 0x0E, 0xBE, 0x8F, 0x53, 0x2C, 0x6C, 0x1B, 0x61, 0x10, 
	0x10, 0x00, 0x18, 0xC9, 0x21, 0x69, 0x1A, 0x3E, 0xA5, 0xC4, 
	0x6D, 0xAD, 0xA6, 0x88, 0x81, 0xE7, 0x21, 0xF0, 0x3C, 0x30, 
	0xF3, 0x1F, 0x87, 0x48, 0xAD, 0x95, 0x2E, 0x59, 0x4C, 0xA7, 
	0xD3, 0x7B, 0x66, 0xDE, 0x10, 0x11, 0x0C, 0xC3, 0x40, 0x1C, 
	0xC7, 0x88, 0xA2, 0xE8, 0xEC, 0xF6, 0xC1, 0x60, 0x00, 0xC7, 
	0x71, 0x94, 0x4E, 0x55, 0xD0, 0x6C, 0x36, 0x01, 0x00, 0xEF, 
	0xE3, 0x31, 0x7E, 0x50, 0x8C, 0x52, 0xA9, 0x94, 0xD9, 0x6B, 
	0xB8, 0x12, 0xED, 0x76, 0xBB, 0xD0, 0x60, 0xDB, 0x6A, 0xB5, 
	0xE8, 0x65, 0xB9, 0xFC, 0x28, 0x12, 0xBF, 0xEA, 0x3A, 0x6C, 
	0xDB, 0xA6, 0x74, 0xEB, 0x94, 0x47, 0xEC, 0x76, 0xBB, 0xDC, 
	0x39, 0xE9, 0x3F, 0x25, 0xCE, 0x0F, 0xF1, 0x92, 0x49, 0x91, 
	0x38, 0x13, 0x62, 0x1A, 0x52, 0xCA, 0xAA, 0x10, 0x02, 0x6F, 
	0xC3, 0xE1, 0xBF, 0x99, 0x68, 0x39, 0x62, 0x53, 0x08, 0xF1, 
	0x95, 0x16, 0x77, 0xA2, 0x08, 0x46, 0xB9, 0xCC, 0x17, 0x0D, 
	0xA4, 0x94, 0x24, 0xA5, 0x7C, 0x14, 0x42, 0x2C, 0xF3, 0x88, 
	0x13, 0xCB, 0x4A, 0x9B, 0x50, 0x5E, 0x05, 0x77, 0x00, 0x64, 
	0x18, 0x86, 0x85, 0xA5, 0x4F, 0x2C, 0x0B, 0x8D, 0x46, 0x83, 
	0x01, 0x70, 0x61, 0x0B, 0x8B, 0xD1, 0xE8, 0xAA, 0x7F, 0xA1, 
	0x42, 0x74, 0xB6, 0x5B, 0x30, 0x33, 0xAA, 0xFD, 0x3E, 0x4C, 
	0xD3, 0x84, 0xEB, 0xBA, 0x70, 0x1C, 0xE7, 0x4C, 0x10, 0xCD, 
	0xE7, 0xF9, 0x06, 0xCF, 0xB3, 0xD9, 0x86, 0x34, 0x2D, 0x33, 
	0x4C, 0xDF, 0xBB, 0x1D, 0x7C, 0xD7, 0xCD, 0xBE, 0xFB, 0xC3, 
	0x03, 0x8C, 0xF5, 0x9A, 0x93, 0x69, 0x54, 0x61, 0x54, 0xEA, 
	0x75, 0x26, 0x5D, 0x47, 0xB9, 0x52, 0x51, 0xE4, 0x30, 0x08, 
	0x70, 0xD8, 0xEF, 0x8F, 0x4A, 0x02, 0x8E, 0x93, 0xB8, 0x5B, 
	0xAD, 0xC0, 0x71, 0x4C, 0x00, 0xF0, 0x0B, 0x75, 0x86, 0x92, 
	0x76, 0x73, 0x70, 0x33, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x49, 
	0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& disabled_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( disabled_png, sizeof( disabled_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
}


#endif //DISABLED_PNG_H
