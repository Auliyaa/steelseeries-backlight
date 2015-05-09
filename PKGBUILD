# Maintainer : Ludwig Fiolka <ludwig (dot) fiolka at gmail>

_name=steelseeries-backlight
pkgname=kbd-light
pkgver=v0.1.r0.g6d1949c
pkgrel=1
pkgdesc="A very thin command-line utility to switch the light configuration of your MSI keyboard."
arch=('i686' 'x86_64')
url="https://github.com/Auliyaa/steelseeries-backlight"
license=('LGPL3')
depends=('hidapi')
makedepends=('tclap')

source=('git+https://github.com/Auliyaa/steelseeries-backlight.git')
md5sums=('SKIP')

pkgver() {
  cd "${srcdir}/${_name}"
  git checkout v${pkgver}
  git describe --long | sed -r 's/([^-]*-g)/r\1/;s/-/./g'
}

prepare() {
  cd "${srcdir}/${_name}"
  mkdir build
  cd build
  cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
}

build() {
  cd "${srcdir}/${_name}/build"
  make
}

package() {
  cd "${srcdir}/${_name}/build"
  make DESTDIR="${pkgdir}" install
}
