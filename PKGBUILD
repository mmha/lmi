pkgname=lmi
pkgver=0.1
pkgrel=1
pkgdesc="Linear algebra library for C++"
arch=('x86' 'x86_64' 'armv7h')
license=('boost')
makedepends=('cmake')

build() {
	cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
	make
}

package() {
	make DESTDIR="$pkgdir" install
}