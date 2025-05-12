# libtorch-example
This repository demonstrates linking errors that occur when using delay-loaded LibTorch.


## 复现步骤:
1. Install libtorch
```
pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu118
```

Then modify the Torch_DIR in CMakeLists.txt to point to your libtorch path, for example:
```

set(Torch_DIR C:/Users/admin/anaconda3/Lib/site-packages/torch/share/cmake/Torch)
```

2. Configure and build
If cmake is in your environment variables:

```
cmake .. -G"Visual Studio 16 2019"
```

Ensure there are no errors, then:
```
cmake --build . --target ALL_BUILD --config RelWithDebInfo --verbose
```

After compiling, you will see an error similar to the following:

```
  C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Tools\MSVC\14.29.30133\bin\HostX64\x64\link.exe /ERRORREPORT:QUEUE /OUT:"C:\Users\kohill\Desktop\wo
  rkspace\torch-delay-load-hook-test\libtorch-example\build\RelWithDebInfo\libtorch-example.exe" /INCREMENTAL /ILK:"libtorch-example.dir\RelWithDebInfo\libtorch-exampl 
  e.ilk" /NOLOGO /LIBPATH:"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" "C:\Program Files (x86)\Torch\lib\c10.lib" "C:\Program Files (x86)\Torch\l 
  ib\kineto.lib" "C:\Program Files (x86)\Torch\lib\caffe2_nvrtc.lib" "C:\Program Files (x86)\Torch\lib\c10_cuda.lib" "C:\Program Files (x86)\Torch\lib\caffe2_nvrtc.lib 
  " "C:\Program Files (x86)\Torch\lib\c10_cuda.lib" "C:\Program Files (x86)\Torch\lib\torch.lib" "C:\Program Files (x86)\Torch\lib\torch_cuda.lib" "C:\Program Files (x 
  86)\Torch\lib\torch_cpu.lib" C:\Users\kohill\anaconda3\Library\lib\libprotobuf.lib "-INCLUDE:?warp_size@cuda@at@@YAHXZ" "C:\Program Files (x86)\Torch\lib\c10_cuda.li 
  b" "C:\Program Files (x86)\Torch\lib\c10.lib" "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64\cudart.lib" "C:\Program Files\NVIDIA Corporation\NvTo 
  olsExt\lib\x64\nvToolsExt64_1.lib" kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib Delayimp.lib  
  /DELAYLOAD:torch_cuda.dll /DELAYLOAD:torch_cpu.dll /DELAYLOAD:c10.dll /DELAYLOAD:c10_cuda.dll /MANIFEST /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /manifest:e 
  mbed /DEBUG /PDB:"C:/Users/kohill/Desktop/workspace/torch-delay-load-hook-test/libtorch-example/build/RelWithDebInfo/libtorch-example.pdb" /SUBSYSTEM:CONSOLE /TLBID: 
  1 /DYNAMICBASE /NXCOMPAT /IMPLIB:"C:/Users/kohill/Desktop/workspace/torch-delay-load-hook-test/libtorch-example/build/RelWithDebInfo/libtorch-example.lib" /MACHINE:X 
  64  /machine:x64 "libtorch-example.dir\RelWithDebInfo\main.obj"
LINK : fatal error LNK1194: 无法延迟加载“c10_cuda.dll”，原因在于数据符号“"__declspec(dllimport) struct std::atomic<class c10::cuda::CUDACachingAllocator::CUDAAllocator *> c10::cuda::
CUDACachingAllocator::allocator" (__imp_?allocator@CUDACachingAllocator@cuda@c10@@3U?$atomic@PEAVCUDAAllocator@CUDACachingAllocator@cuda@c10@@@std@@A)”的导入；链接时不
使用 /DELA
YLOAD:c10_cuda.dll [C:\Users\kohill\Desktop\workspace\torch-delay-load-hook-test\libtorch-example\build\libtorch-example.vcxproj]
已完成生成项目“C:\Users\kohill\Desktop\workspace\torch-delay-load-hook-test\libtorch-example\build\libtorch-example.vcxproj”(默认目标)的操作 - 失败。

已完成生成项目“C:\Users\kohill\Desktop\workspace\torch-delay-load-hook-test\libtorch-example\build\ALL_BUILD.vcxproj”(默认目标)的操作 - 失败。


生成失败。

“C:\Users\kohill\Desktop\workspace\torch-delay-load-hook-test\libtorch-example\build\ALL_BUILD.vcxproj”(默认目标) (1) ->
“C:\Users\kohill\Desktop\workspace\torch-delay-load-hook-test\libtorch-example\build\libtorch-example.vcxproj”(默认目标) (3) ->
(Link 目标) ->
  LINK : fatal error LNK1194: 无法延迟加载“c10_cuda.dll”，原因在于数据符号“"__declspec(dllimport) struct std::atomic<class c10::cuda::CUDACachingAllocator::CUDAAllocator *> c10::cuda
::CUDACachingAllocator::allocator" (__imp_?allocator@CUDACachingAllocator@cuda@c10@@3U?$atomic@PEAVCUDAAllocator@CUDACachingAllocator@cuda@c10@@@std@@A)”的导入；链接时 不使用 /DE
LAYLOAD:c10_cuda.dll [C:\Users\kohill\Desktop\workspace\torch-delay-load-hook-test\libtorch-example\build\libtorch-example.vcxproj]

    0 个警告
    1 个错误

已用时间 00:00:01.08
```
