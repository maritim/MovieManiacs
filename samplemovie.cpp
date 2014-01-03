#include "samplemovie.h"

#include <QtCore>

samplemovie::samplemovie(void) {
}

/*samplemovie::samplemovie(const samplemovie& smplMovie)
{
    this->setMoviePoster(smplMovie.getMoviePoster());
    this->setName(smplMovie.getName());
}*/

void samplemovie::setMoviePoster(QImage moviePoster) {
    this->moviePoster = moviePoster;
}

QImage samplemovie::getMoviePoster(void) const {
    return this->moviePoster;
}
