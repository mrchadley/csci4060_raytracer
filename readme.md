# Concurrent Raytracer
## Sequential, OpenMP, Posix Threads, OpenCL*

*OpenCL version not yet implemented.

<br>

### About:
This is my final project for a course I took in university, CSCI 4060U: Massively Parallel Programming. My plan was to create a simple raytracing app that could use different APIs for parallelism and compare them to each other and to a sequential version. The APIs I chose were OpenMP, POSIX Threads and OpenCL. Unfortuately, with other final projects, presentations and exams to worry about, I was not able to start on the OpenCL version in time to meet the submission deadline.

I do intend to implement the OpenCL version, as well as add functionality for loading a scene from a file, add support for multiple shapes (instead of just spheres), and make general improvements.

<br>

### How To Run:
- Open the main folder in bash terminal.
- Run the "make" command to build the app. The executable will be made in the "output/" folder.
- Run the command "cd output/" to switch into it.
- Run the command "./raytracer \<method> \<width> \<height>" to run the app.
> for \<method> specify "sequential", "openmp", "pthread", or "opencl". \<width> and \<height> specify the size in pixels of the output image.
- This will create an image file in the output folder "\<method>.png" and print the render time (in seconds) to the console.
