# Planning
Building the system using bottom-to-top approach.

## Phase-1
Lower level components such as Tensors, NNInterface needs to be built first. For now reliability on largers thirdparty components such as tensorflow etc can be avoided, we could define place holders for them and return a predefined values.

For now only one tagger (**scene tagger**) can be targed which uses only **image classifier**. 
The build can be based on make, so need to define and update **Makefile**s. It is good practice to have tests for all the components.

- [x] Define structure of the project
- [ ] Integrate thirdparty dependencies
    - [X] OpenCV
    - [ ] Json parser
    - [ ] TensorflowLite
    - [ ] Tensorflow
    - [ ] GTest
- [ ] Develop the build system

The following components are to be developed in this phase:
- [X] Tensor
- [X] Context, Config
- [X] NNInterface
- [X] Framework
- [ ] ImageClassifier
- [ ] MappingInfo
- [ ] ImageTagMapper
- [ ] ImageTagFilter
- [ ] SceneTagger
- [ ] TaggerFactory
- [ ] Engine

### Notes
- For implementing Tensor3D<type>, https://github.com/maitek/tensor-cpp/blob/master/tensor.hpp could be referred.

## Phase-2
To demonstrate extensibility of the system, have decorators/wrappers defined around ImageClassifier.
- [ ] define with-flip wrapper for ImageClassifier
- [ ] define on-center for ImageClassifier
- [ ] define remove-set wrapper for ImageTagFilterer

Integrate **tensorflow** with NNInterface and execute the engine on actual model
- [ ] Link tensorflow lite c++ library (https://www.tensorflow.org/lite/api_docs/cc)
- [ ] Get a simple image classifier model and manually develop the mapping data using the labels from model
- [ ] Execute model on real image to get the output tags

- [ ] Add logger

## Next Phases
- [ ] Adding ObjectDetector components
- [ ] Define ImageTagger which uses both classifier & object detector
- [ ] Use builder pattern to construct components during runtime.
- [ ] Optimizing the runtime by understanding the bottlenecks and measuring all critical operations.
- [ ] Defining metrics such as model runtime, component runtimes etc.
