FROM zeromqorg/czmq

USER root

RUN apt-get -y install curl libssl-dev

# install cmake >=0.10 (to have gtest macro)
RUN curl -L https://cmake.org/files/v3.12/cmake-3.12.2.tar.gz -o /tmp/cmake.tar.gz \
	&& cd /tmp \
	&& tar xzvf cmake.tar.gz \
	&& cd cmake-3.12.2 \
	&& ./configure \
	&& make \
	&& make install


# install gtest
RUN curl -L https://github.com/google/googletest/archive/release-1.8.1.tar.gz -o /tmp/gtest.tar.gz \
	&& cd /tmp \
	&& tar xzvf gtest.tar.gz \
	&& mkdir build_gtest && cd build_gtest \
	&& cmake -DBUILD_SHARED_LIBS=ON ../googletest-release-1.8.1/googletest/ \
	&& make \
	&& cp -r ../googletest-release-1.8.1/googletest/include/gtest /usr/local/include/ \
	&& cp lib*.so /usr/lib/


WORKDIR /app
COPY . /app
RUN apt-get -y install nano

# build app
RUN cd /app \
	&& cmake . \
	&& make
