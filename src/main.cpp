#pragma warning(push, 0)
#include <torch/script.h>
#include <torch/torch.h>
#include <c10/cuda/CUDACachingAllocator.h>
#pragma warning(pop)
#include <iostream>
int main()
{
    auto model = torch::jit::load("model.pt");
    // Example input tensor
    at::Tensor input = torch::randn({1, 3, 224, 224}); // Adjust dimensions as needed
    // Run the model
    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(input);
    at::Tensor output = model.forward(inputs).toTensor();
    ::c10::cuda::CUDACachingAllocator::get()->emptyCache();
    return 0;
}