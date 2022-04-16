// Generates TypeScript code for a given .proto file.
//
#ifndef PROTOBUF_TS_GENERATOR_H__
#define PROTOBUF_TS_GENERATOR_H__

#include <string>
#include <vector>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/plugin.h>

namespace google
{
  namespace protobuf
  {

    class Descriptor;
    class EnumDescriptor;
    class FieldDescriptor;
    class OneofDescriptor;
    class FileDescriptor;
    class ServiceDescriptor;

    namespace io
    {
      class Printer;
    }
    namespace compiler
    {
      class CodeGenerator;
      class CodeGeneratorRequest;
      class CodeGeneratorResponse;
      class GeneratorContext;
    }
  } // namespace protobuf
} // namespace google

namespace ts
{

  struct GeneratorOptions
  {
    // Output path.
    std::string output_dir;
    // Namespace prefix.
    std::string name;
    // Input to Output ratio
    std::string ratio;
    // Dependencies handling
    std::string deps;
    // Generate generic services.
    bool services;

    GeneratorOptions()
        : output_dir("."),
          name("YourNamespaceHere"),
          ratio(""),
          deps(""),
          services(false),
          library(""),
          extension(".ts") {}

    bool ParseFromOptions(
        const std::vector<std::pair<std::string, std::string>> &options,
        std::string *error);

    // Returns the file name extension to use for generated code.
    std::string GetFileNameExtension() const { return extension; }

    enum OutputMode
    {
      // Create an output file for each input .proto file.
      kOneOutputFilePerInputFile,
      // Create an output file for each type.
      kOneOutputFilePerService,
      // Put everything in a single file named by the library option.
      kEverythingInOneFile,
    };

    // Indicates how to output the generated code based on the provided options.
    OutputMode output_mode() const;
    // Create a library with name <name>_lib.ts rather than a separate .ts file
    // per type?
    std::string library;
    // The extension to use for output file names.
    std::string extension;
  };

  using namespace google::protobuf;

  // CodeGenerator implementation which generates a TypeScript source file and
  // header.
  class Generator : public compiler::CodeGenerator
  {
  public:
    Generator() {}
    virtual ~Generator() {}

    virtual bool Generate(const FileDescriptor *file,
                          const std::string &parameter, compiler::GeneratorContext *context,
                          std::string *error) const
    {
      *error = "Unimplemented Generate() method. Call GenerateAll() instead.";
      return false;
    }

    virtual bool HasGenerateAll() const { return true; }

    virtual bool GenerateAll(const std::vector<const FileDescriptor *> &files,
                             const std::string &parameter,
                             compiler::GeneratorContext *context, std::string *error) const;

  private:
    void Header(std::map<std::string, std::string> *vars,
                io::Printer *printer) const;
    void ES6Imports(const FileDescriptor *file, io::Printer *printer,
                    std::map<std::string, std::string> *vars) const;
    bool File(const FileDescriptor *file, const GeneratorOptions &options,
              compiler::GeneratorContext *context) const;
    void File(io::Printer *printer, const FileDescriptor *file,
              const GeneratorOptions &options,
              std::map<std::string, std::string> *vars) const;
    void ClassesAndEnums(io::Printer *printer, const FileDescriptor *file,
                         std::map<std::string, std::string> *vars) const;
    void ClassConstructor(io::Printer *printer,
                          std::map<std::string, std::string> *vars) const;
    void Class(io::Printer *printer, const Descriptor *desc,
               std::map<std::string, std::string> *vars) const;
    void Fields(io::Printer *printer, const Descriptor *desc,
                std::map<std::string, std::string> *vars) const;
    void Field(io::Printer *printer, const FieldDescriptor *desc,
               std::map<std::string, std::string> *vars) const;
    void DeserializeBinary(io::Printer *printer, const Descriptor *desc,
                           std::map<std::string, std::string> *vars) const;
    void DeserializeBinaryField(io::Printer *printer,
                                const FieldDescriptor *field,
                                std::map<std::string, std::string> *vars,
                                bool tmp = false) const;
    void SerializeBinary(io::Printer *printer, const Descriptor *desc,
                         std::map<std::string, std::string> *vars) const;
    void SerializeBinaryField(io::Printer *printer, const FieldDescriptor *field,
                              std::map<std::string, std::string> *vars) const;
    void OneofCaseDefinition(io::Printer *printer, const OneofDescriptor *oneof,
                             std::map<std::string, std::string> *vars) const;
    void Nested(io::Printer *printer, const Descriptor *desc,
                std::map<std::string, std::string> *vars) const;
    void Enum(io::Printer *printer, const EnumDescriptor *enumdesc,
              std::map<std::string, std::string> *vars) const;
    void ServiceUtil(io::Printer *printer) const;
    void ServiceClass(io::Printer *printer, const ServiceDescriptor *des,
                      std::map<std::string, std::string> *vars) const;
  };

} // namespace ts

#endif // PROTOBUF_TS_GENERATOR_H__
