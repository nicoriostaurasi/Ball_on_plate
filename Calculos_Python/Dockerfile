FROM borda/docker_python-opencv-ffmpeg

RUN apt-get update \
    && apt-get install -y libzbar0 python3.9-tk\
    && pip install pyzbar \
    && pip install pyperclip \
    && pip install pyserial \
    && pip install tk \
    && pip install pandas \
    && pip install -U scikit-fuzzy

ADD *.py ./
ADD image_settings.json .
