#include "PagedView.h"

#define SSD1306_NO_SPLASH

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDR 0x3C


// SIZE
Size::Size(uint8_t _width, uint8_t _height) : width(_width), height(_height) {}

Point Size::GetCenter(Point offset = Point(0, 0))
{
  return Point((width / 2) + (offset.x / 2), (height / 2) + (offset.y / 2));
}
// POINT

Point::Point(uint8_t _x, uint8_t _y) : x(_x), y(_y) {}

// RELATIVE POINT

RelativePoint::RelativePoint(Point p, Size s)
{
  this->x = (double)p.x / (double)s.width;
  this->y = (double)p.y / (double)s.height;

}

RelativePoint::RelativePoint(double _x, double _y)
{

  _x = _x > 1 ? 1 : _x;
  _x = _x < 0 ? 0 : _x;

  _y = _y > 1 ? 1 : _y;
  _y = _y < 0 ? 0 : _y;

  this->x = _x;
  this->y = _y;
}

Point RelativePoint::ToPoint(Size size)
{

  x = x > 1 ? 1 : x;
  x = x < 0 ? 0 : x;

  y = y > 1 ? 1 : y;
  y = y < 0 ? 0 : y;

  return Point((uint8_t)(x * (double)size.width), (uint8_t)(y * (double)size.height));
}

// --- PAGED VIEW  ---

namespace PagedView
{
  
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  Page *currentPage = nullptr;

  bool Begin()
  {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR))
      return false;

    display.clearDisplay();

    display.display();

    return true;
  }

  void ClearDisplay()
  {
    display.clearDisplay();
    display.display();
  }

  void HandleInput(BtnInput input)
  {
    if (currentPage != nullptr)
      currentPage->OnInput(input);
  }

  void Periodic()
  {
    if (currentPage != nullptr)
      currentPage->Periodic();
  }

  void SwitchToPage(Page *page)
  {
    if(currentPage == page) return;
    
    if(currentPage != nullptr)
    currentPage->OnExit();

      if (page == nullptr) currentPage = nullptr;
      else
      {
        page->OnLoad();
        currentPage = page;
        page->Draw();
      }
  }

  Page *GetCurrentPage()
  {
    return currentPage;
  }
}

// --- PAGE  ---

void Page::Close()
{
  if (PagedView::GetCurrentPage() == this)
    PagedView::SwitchToPage(nullptr);
}

void Page::Show()
{
  if (PagedView::GetCurrentPage() == nullptr)
    PagedView::SwitchToPage(this);
  else
  {
    PagedView::GetCurrentPage()->Close();
    PagedView::SwitchToPage(this);
  }
}

bool Page::IsShown()
{
  return PagedView::GetCurrentPage() == this;
}

void Page::Draw()
{
  if (PagedView::GetCurrentPage() != this)
    return;

  for (int i = 0; i < this->componentsCount; i++)
  {
    PageComponent *comp = this->components[i];

    if(comp->IsVisible())
    comp->Draw();
  }
}

void Page::AddComponent(PageComponent *component)
{
  this->components[componentsCount++] = component;
}

// --- PAGE COMPONENT ---

PageComponent::PageComponent(Page *_parentPage, Point _pos)
{
  this->parentPage = _parentPage;
  this->pos = _pos;
}

PageComponent::PageComponent(Page *_parentPage, RelativePoint _pos)
{
  this->parentPage = _parentPage;
  this->pos = _pos.ToPoint(Size(SCREEN_WIDTH, SCREEN_HEIGHT));
}

void PageComponent::SetVisible(bool v)
{
  this->visible = v;
  if (this->parentPage->IsShown())
    this->Draw();
}

bool PageComponent::IsVisible()
{
  return this->visible;
}