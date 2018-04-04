#include "hyperlink.h"


namespace HYPERLINK {

void REPO()
{
    QDesktopServices::openUrl(QUrl("https://ithub.com/Eve-ning/amber", QUrl::TolerantMode));
}

void WIKI()
{
    QDesktopServices::openUrl(QUrl("https://ithub.com/Eve-ning/amber/wiki", QUrl::TolerantMode));
}

void RELEASES()
{
    QDesktopServices::openUrl(QUrl("https://ithub.com/Eve-ning/amber/releases", QUrl::TolerantMode));
}

void CONTACT()
{
    QDesktopServices::openUrl(QUrl("https://su.ppy.sh/forum/ucp.php?i=pm&mode=compose&u=2193881", QUrl::TolerantMode));
}





}
