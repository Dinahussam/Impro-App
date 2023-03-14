# Image Processing Application

## Table of contents:
- [Introduction](#introduction)
- [Project Features](#project-features)
- [Project Structure](#project-structure)
- [Quick Preview](#quick-preview)
- [Requirements to run](#Requirements-to-run)
- [Run the project](#Run-the-project)
- [Try a demo](#Try-a-demo)
- [Team]()


### Introduction
It’s an image processing implementation functions project implemented in C++ with a desktop application (Qt) that consists of five tabs that let the user add noise to an image, filter the added noise, view different types of histograms, apply thresholds to an image, and create hybrid images. 

### Project Features
In this project you can:
- [x] Add different types of noise to the image:
  - Salt and Paper noise.
  - Uniform noise.
  - Gaussian noise.
- [x] Using different types of filtering:
  - Average filter .
  - Gaussian filter.
  - Median filter.
- [x] Detect edges in the image using:
  - Sobel edge detector.
  - Roberts edge detector.
  - Prewitt edge detector.
  - Canny edge detector.
- [x] Draw Histograms and Distribution curves for the uploaded image.
- [x] Equalize and Normalize the image.
- [x] Create Local, and Global thresholding.
- [x] Transform the image from color to gray scale image and plot Red, Green, and Blue histograms with their cumulative curves.
- [x] Apply filtering in the frequency domain.
  - Ideal Low Pass filter (smoothing).
  - Ideal High Pass filter (sharpening).
- [x] Create Hybrid images.


### Project Structure
Imgpro is built using:
- C++/Opencv:
  - Opencv 14/15/16 versions

- QT framework:
  - QT 6.4.2 version

```
QT_GUI_TASK_1
├─  Filters
│  ├─ add_noise 
│  ├─ convolution
│  ├─ edge_detection
│  ├─ helper_functions
│  └─ remove_noise
├─  Frequency
│  └─ frequency
├─  Histogram
│  └─ Histogram
├─  Threshold
│  └─ Thresholding
├─  UI
│  ├─ cannyparameters 
│  ├─ gaussiannoiseparameters
│  ├─ qcustomplot
│  ├─ saltpepperparameters
│  ├─ thresholdwindow
│  └─ uniformnoiseparameters
├─  Forms
├─  Icons
├─  Images
├─  Common
├─  imageClass
├─  main
├─  mainwindow
README.md
```

### Quick Preview

#### Add different types of noises to the image and filtering them.
![Filter Tab](https://user-images.githubusercontent.com/94166833/225074632-50d99267-58bf-45fc-90b8-8254eea2662c.gif)
#### Draw histograms and distribution curves for the uploaded image.
![Histogram Tab](https://user-images.githubusercontent.com/94166833/225074554-13bf3c58-7d5b-4383-8b95-8a414e9de45f.gif)
#### Detect edges in the image using edge detectors
![Edge Detection Tab](https://user-images.githubusercontent.com/94166833/225074768-da7e9fca-e547-4fdb-a8eb-823957d46aaf.gif)
#### Equalization, Normalization, Local, and Global thresholding to the image.
![Threshold Tab](https://user-images.githubusercontent.com/94166833/225074321-fd67c472-35f5-4a32-bcfb-5444f40d6fe2.gif)
#### Low and High pass filtering and create Hybrid images.
![Hybrid Tab](https://user-images.githubusercontent.com/94166833/225074411-a0d8a5cd-3f5b-4b2c-b8b3-4e44015ed536.gif)


### Requirements to run 

[ Read Here ! ](https://www.mediafire.com/file/0how1ixgl0vnkgk/CVisioneer+Setup.exe/file)


### Run the project


### Try a demo

[ Download Here !](https://www.mediafire.com/file/0how1ixgl0vnkgk/CVisioneer+Setup.exe/file)


### Team

Second Semester - Biomedical Computer Vision (SBE3230) class project created by:

| Team Members' Names                                  | Section | B.N. |
|------------------------------------------------------|:-------:|:----:|
| [Dina Hussam](https://github.com/Dinahussam)         |    1    |  28  |
| [Omar Ahmed ](https://github.com/omaranwar21)        |    2    |  2   |
| [Omar saad ](https://github.com/Omar-Saad-ELGharbawy)|    2    |  3   |
| [Mohamed Ahmed](https://github.com/MohamedAIsmail)   |    2    |  16  |
| [Neveen Mohamed](https://github.com/NeveenMohamed)   |    2    |  49  |
