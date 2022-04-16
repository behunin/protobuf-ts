# protobuf-ts
Protoc plugin to generate typescript client code from .proto files.

# Build

1. Make Build Directory.
2. Change to build directory.
3. ``cmake ..``
4. ``make``
5. Rename protobuf-ts to protoc-gen-protobuf-ts.
6. Move protoc-gen-protobuf-ts to desired location.

# Use

***Make sure to include .exe on windows.***

``protoc --plugin=protoc-gen-protobuf-ts=path/to/protoc-gen-protobuf-ts.exe --protobuf-ts_out=name=YourNameSpaceHere:$OUT_DIR test.proto test1.proto test2.proto``

Generator Options are as follows:

  **Name**: the file name used for the output file, this is used with the A~1 ratio option.

``protoc --plugin=protoc-gen-protobuf-ts=path/to/protoc-gen-protobuf-ts --protobuf-ts_out=name=YourNameSpaceHere:$OUT_DIR test.proto test1.proto test2.proto``

  **Ratio**:  input to output ratio – if not used the default ratio is one output to each input file.
   ```
 S~1 – print one file for each service definition.
 A~1 – print one file from all input files.
```

``protoc --plugin=protoc-gen-protobuf-ts=path/to/protoc-gen-protobuf-ts --protobuf-ts_out=ratio=S~1:$OUT_DIR test.proto``

  **Deps**: currently only used with the default one to one output.
   - Print – Prints each dependency in its own file. Then prints import statements for each dependency.
   - Import – Just prints the import statements for each dependency.
   - Include – Prints dependencies in the output file.

``protoc --plugin=protoc-gen-protobuf-ts=path/to/protoc-gen-protobuf-ts --protobuf-ts_out=deps=print:$OUT_DIR test.proto``

  **Services**: print the generic service definitions or not – can be used with any output ratio.

``protoc --plugin=protoc-gen-protobuf-ts=path/to/protoc-gen-protobuf-ts --protobuf-ts_out=services:$OUT_DIR test.proto``

# Client Library
[gRPC-Web-Ts](https://github.com/behunin/grpc-web-ts)
