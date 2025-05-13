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
    /*! The following two lines will cause a link error like:
        LINK : fatal error LNK1194: 无法延迟加载“torch_cpu.dll”，原因在于数据符号“"__declspec(dllimport) struct at::indexing::EllipsisIndexType const at::indexing::Ellipsis" (__imp_?Ellipsis@indexing@at@@3UEllipsisIndexType@12@B)”的导入；链接时不使用 /DELAYLOAD:torch_cpu.dll 
    */
    torch::Tensor tensor = torch::ones({2, 3, 4, 5});
    torch::Tensor result = tensor.index({torch::indexing::Ellipsis, 0});
    return 0;
}