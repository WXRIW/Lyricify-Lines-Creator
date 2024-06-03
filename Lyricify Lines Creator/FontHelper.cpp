/************************************************************************
 * Filename:    FontHelper.cpp
 * Description: 字体帮助类实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "FontHelper.h"

SIZE FontHelper::CalculateTextSize(const wchar_t* text, const wchar_t* fontName, int fontSize, int dpiScale, int fontWeight, bool italic, bool underline, bool strikeout)
{
    SIZE textSize = { 0 };

    if (text && fontName && fontSize > 0)
    {
        // 创建字体
        HFONT hFont = CreateFont(fontSize * dpiScale, 0, 0, 0, fontWeight, italic, underline, strikeout, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, fontName);

        if (hFont)
        {
            HDC hdc = GetDC(NULL);
            if (hdc)
            {
                HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

                // 使用 DrawText 函数计算文本尺寸
                RECT rect = { 0, 0, 0, 0 };
                DrawText(hdc, text, -1, &rect, DT_CALCRECT);

                textSize.cx = (rect.right - rect.left) / dpiScale;
                textSize.cy = (rect.bottom - rect.top) / dpiScale;

                // 恢复原来的字体
                SelectObject(hdc, hOldFont);
                ReleaseDC(NULL, hdc);
            }

            // 释放字体资源
            DeleteObject(hFont);
        }
    }

    return textSize;
}