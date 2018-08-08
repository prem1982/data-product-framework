FROM data-product-python-build
LABEL maintainer="karanhaar.singh@bossanova.com" \
    version="9.0-cudnn7-0.0.1"

# CUDA version components
ENV CUDA_MAJOR 9
ENV CUDA_MINOR 0
ENV CUDA_PATCH 176
ENV CUDA_BUILD 3

# Full CUDA versions
ENV CUDA_MAJOR_MINOR $CUDA_MAJOR.$CUDA_MINOR
ENV CUDA_VERSION $CUDA_MAJOR_MINOR.$CUDA_PATCH
ENV CUDA_VERSION_BUILD $CUDA_VERSION.$CUDA_BUILD

# CUDA packages
ENV CUDA_PKG_SUFFIX $CUDA_MAJOR-$CUDA_MINOR
ENV CUDART_PKG_VERSION $CUDA_VERSION-1
ENV CUBLAS_PKG_VERSION $CUDA_VERSION_BUILD-1

# Other CUDA-related library versions
ENV NCCL_VERSION 2.2.12
ENV CUDNN_VERSION 7.1.4.18


# Install base packages (https://gitlab.com/nvidia/cuda/blob/ubuntu16.04/9.0/base/Dockerfile)
RUN apt-get update -y \
	&& apt-get install -y --no-install-recommends \
		ca-certificates \
		apt-transport-https \
		gnupg-curl \
    && rm -rf /var/lib/apt/lists/* \
    && NVIDIA_GPGKEY_SUM=d1be581509378368edeec8c1eb2958702feedf3bc3d17011adbf24efacce4ab5 \
    && NVIDIA_GPGKEY_FPR=ae09fe4bbd223a84b2ccfce3f60f4b3d7fa2af80 \
    && apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1604/x86_64/7fa2af80.pub \
    && apt-key adv --export --no-emit-version -a $NVIDIA_GPGKEY_FPR | tail -n +5 > cudasign.pub \
    && echo "$NVIDIA_GPGKEY_SUM  cudasign.pub" | sha256sum -c --strict - && rm cudasign.pub \
    && echo "deb https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1604/x86_64 /" > /etc/apt/sources.list.d/cuda.list \
    && echo "deb https://developer.download.nvidia.com/compute/machine-learning/repos/ubuntu1604/x86_64 /" > /etc/apt/sources.list.d/nvidia-ml.list

RUN apt-get update -y \
	&& apt-get install -y --no-install-recommends \
        cuda-cudart-$CUDA_PKG_SUFFIX=$CUDART_PKG_VERSION \
    && ln -s cuda-$CUDA_PKG_SUFFIX /usr/local/cuda \
    && rm -rf /var/lib/apt/lists/*

RUN echo "/usr/local/nvidia/lib" >> /etc/ld.so.conf.d/nvidia.conf \
    && echo "/usr/local/nvidia/lib64" >> /etc/ld.so.conf.d/nvidia.conf


# Install runtime packages (https://gitlab.com/nvidia/cuda/blob/ubuntu16.04/9.0/runtime/Dockerfile)
RUN apt-get update -y \
	&& apt-get install -y --no-install-recommends \
        cuda-libraries-$CUDA_PKG_SUFFIX \
        cuda-cublas-$CUDA_PKG_SUFFIX=$CUBLAS_PKG_VERSION \
        libnccl2=$NCCL_VERSION-1+cuda$CUDA_MAJOR_MINOR \
    && rm -rf /var/lib/apt/lists/*


# Install cudnn (https://gitlab.com/nvidia/cuda/blob/ubuntu16.04/9.0/runtime/cudnn7/Dockerfile)
RUN apt-get update -y \
	&& apt-get install -y --no-install-recommends \
		libcudnn7=$CUDNN_VERSION-1+cuda$CUDA_MAJOR_MINOR \
    && rm -rf /var/lib/apt/lists/*
