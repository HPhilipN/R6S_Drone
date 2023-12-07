// cam.cpp
#include "cam.h"
#include <libcamera/libcamera.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <sys/mman.h>

using namespace libcamera;

std::unique_ptr<CameraManager> cm;
std::shared_ptr<Camera> camera;
std::unique_ptr<CameraConfiguration> config;

void initialize_camera() {
    cm = std::make_unique<CameraManager>();
    int ret = cm->start();
    if (ret) {
        std::cerr << "Failed to start camera manager: " << ret << std::endl;
        exit(EXIT_FAILURE);
    }

    // Find the first camera (assumes only one camera is connected)
    for (auto &cam : cm->cameras()) {
        camera = cam;
        break;
    }

    if (!camera) {
        std::cerr << "No cameras available" << std::endl;
        exit(EXIT_FAILURE);
    }

    ret = camera->acquire();
    if (ret) {
        std::cerr << "Failed to acquire camera" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Camera is initialized\n";
}

void capture_image() {
    // Generate and configure the camera for still capture
    config = camera->generateConfiguration({StreamRole::StillCapture});
    if (!config || config->size() != 1) {
        std::cerr << "Failed to generate configuration\n";
        return;
    }

    StreamConfiguration &streamConfig = config->at(0);
    streamConfig.size.width = 640;
    streamConfig.size.height = 480;

    CameraConfiguration::Status validationStatus = config->validate();
    if (validationStatus == CameraConfiguration::Invalid) {
        std::cerr << "Invalid camera configuration\n";
        return;
    }

    if (camera->configure(config.get()) < 0) {
        std::cerr << "Failed to configure the camera\n";
        return;
    }

    // Create buffers for the capture
    std::shared_ptr<Camera::Stream> stream = streamConfig.stream();
    unsigned int bufferCount = stream->configuration().bufferCount;
    std::vector<std::unique_ptr<FrameBuffer>> buffers;

    for (unsigned int i = 0; i < bufferCount; ++i) {
        std::unique_ptr<FrameBuffer> buffer = std::make_unique<FrameBuffer>(stream->configuration().stride);
        buffers.push_back(std::move(buffer));
    }

    // Start the camera
    if (camera->start() < 0) {
        std::cerr << "Failed to start the camera\n";
        return;
    }

    // Queue buffers and capture an image
    for (auto &buffer : buffers) {
        if (camera->queueBuffer(buffer.get()) < 0) {
            std::cerr << "Failed to queue buffer\n";
            return;
        }
    }

    FrameBuffer *completedBuffer = nullptr;
    while (true) {
        Request *request = camera->waitForRequest();
        if (!request) {
            std::cerr << "Failed to wait for request\n";
            break;
        }
        if (request->status() == Request::RequestComplete) {
            completedBuffer = request->findBuffer(stream.get());
            break;
        }
    }

    // Process the captured image
    if (completedBuffer) {
        FrameBuffer::Plane plane = completedBuffer->planes().front();
        void *memory = mmap(nullptr, plane.length, PROT_READ, MAP_SHARED, plane.fd.fd(), 0);
        if (memory == MAP_FAILED) {
            std::cerr << "Failed to map memory\n";
        } else {
            // Save the image in PPM format
            std::ofstream file("captured_image.ppm", std::ios::binary);
            if (file) {
                file << "P6\n" << streamConfig.size.width << " " << streamConfig.size.height << "\n255\n";
                file.write(reinterpret_cast<char*>(memory), plane.length);
            } else {
                std::cerr << "Failed to open file for writing\n";
            }

            munmap(memory, plane.length);
        }
    }

    camera->stop();
}

void release_camera() {
    if (camera)
        camera->release();
    if (cm)
        cm->stop();
    std::cout << "Camera released\n";
}
