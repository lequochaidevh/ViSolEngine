    docker build -t u22-opengl-dev .

    docker run -it \
    --device=/dev/dri/card0 \
    --device=/dev/dri/renderD128 \
    --mount type=bind,source=/sys,target=/sys,readonly \
    --group-add video \
    -v $(pwd):/workspace \
    u22-opengl-dev