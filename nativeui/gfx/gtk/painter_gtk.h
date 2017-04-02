// Copyright 2016 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#ifndef NATIVEUI_GFX_GTK_PAINTER_GTK_H_
#define NATIVEUI_GFX_GTK_PAINTER_GTK_H_

#include <stack>

#include "nativeui/gfx/painter.h"

namespace nu {

class PainterGtk : public Painter {
 public:
  explicit PainterGtk(cairo_t* context);
  ~PainterGtk() override;

  // Painter:
  void Save() override;
  void Restore() override;
  void BeginPath() override;
  void ClosePath() override;
  void MoveTo(const PointF& point) override;
  void LineTo(const PointF& point) override;
  void BezierCurveTo(const PointF& cp1,
                     const PointF& cp2,
                     const PointF& ep) override;
  void Rect(const RectF& rect) override;
  void Clip() override;
  void ClipRect(const RectF& rect) override;
  void Translate(const Vector2dF& offset) override;
  void SetColor(Color color) override;
  void SetStrokeColor(Color color) override;
  void SetFillColor(Color color) override;
  void SetLineWidth(float width) override;
  void Stroke() override;
  void Fill() override;
  void StrokeRect(const RectF& rect) override;
  void FillRect(const RectF& rect) override;
  void DrawColoredTextWithFlags(
      const String& text, Font* font, Color color, const RectF& rect,
      int flags) override;

 private:
  // Set source color from stroke or fill color.
  void SetSourceColor(bool stroke);

  cairo_t* context_;

  // Cairo does not distinguish between stroke color and fill color, we have to
  // implement our own.
  struct PainterState {
    Color stroke_color;
    Color fill_color;
  };
  std::stack<PainterState> states_;
};

}  // namespace nu

#endif  // NATIVEUI_GFX_GTK_PAINTER_GTK_H_
