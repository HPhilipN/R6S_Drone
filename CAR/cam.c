// cam.c
#include <raspicam/raspicam.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cam.h"

raspicam::RaspiCam Camera; // Global camera object

// Initialize the camera
void initialize_camera() {
    printf("Opening Camera...\n");
    if (!Camera.open()) {
        fprintf(stderr, "Error opening camera!\n");
        exit(EXIT_FAILURE);
    }
    printf("Camera is initialized\n");
}

// Capture an image and save it to a file
void capture_image() {
    printf("Capturing image...\n");
    sleep(3); // Camera warm-up time

    if (Camera.grab()) {
        unsigned char *data = new unsigned char[Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
        Camera.retrieve(data, raspicam::RASPICAM_FORMAT_RGB);

        FILE *file = fopen("image.ppm", "wb");
        if (file != NULL) {
            fprintf(file, "P6\n# ppm-file created by raspicam\n%d %d\n255\n",
                    Camera.getWidth(), Camera.getHeight());
            fwrite(data, 1, Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB), file);
            fclose(file);
            printf("Image saved at image.ppm\n");
        }

        delete[] data;
    }
}

// Release the camera
void release_camera() {
    Camera.release();
    printf("Camera released\n");
}
