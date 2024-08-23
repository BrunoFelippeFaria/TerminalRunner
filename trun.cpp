#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
using namespace std;
// essa função adiciona os argumentos passados para o programa
string addArgumentos(int argc, char *argv[]) {
  string argumentos;
  for (int i = 2; i < argc; i++) {
    argumentos += " " + string(argv[i]);
  }
  return argumentos;
}

bool existe(string caminho) {
  filesystem::path findc = caminho;
  if (filesystem::exists(findc)) {
    return true;
  }

  void changeTxt();
  return false;
}

string extrairNomeArquivo(const std::string caminho) {
  filesystem::path p(caminho);
  return p.filename().string();
}

// função principal do programa
int main(int argc, char *argv[]) {
  string tipo = "n";
  string arquivo;

  if (argc > 1) {
    arquivo = argv[1];
    // verifica tipo do arquivo e se ele é compativel
    const string exts[] = {".cpp", ".py", ".sh",  ".c",   ".java",
                           ".go",  ".js", ".lua", ".php", ".rs"};
    size_t ext;
    for (size_t i = 0; i < sizeof(exts) / sizeof(exts[0]); i++) {
      ext = arquivo.rfind(exts[i]);
      if (ext != string::npos) {
        tipo = exts[i];
        break;
      }
    }
    // se o arquivo não for compativel
    if (tipo == "n") {
      cout << "tipo invalido\n";
    }

  } else {
    cout << "porfavor, forneça um arquivo\n";
    return 0;
  }

  // variaveis
  string comando;

  // remover a extenção.
  size_t ponto = arquivo.find(".");
  string exec = arquivo.substr(0, ponto);

  bool caminhoCompleto = false;
  size_t dir = arquivo.rfind("/");

  if (dir != string::npos) {
    caminhoCompleto = true;
  }

  // cmake
  if (existe("CMakeLists.txt") or existe("../CMakeLists.txt")) {
    if (existe("build")) {
      comando = "cd build && make && cd ..";
    }

    else if (existe("../build")) {
      comando = "cd .. && cd build && make && cd ..";
    }

    else {
      comando = "mkdir build && cd build && cmake .. && make && cd ..";
    }

    size_t find = arquivo.find(exec);
    string caminho = arquivo.substr(0, find);

    comando += (caminhoCompleto
                    ? " && " + caminho + "build/" + extrairNomeArquivo(exec)
                    : " && ./" + exec);

  }

  // make

  else if (existe("Makefile") or existe("../Makefile")) {
    if (existe(exec)) {
      system(("rm " + exec).c_str());
    }
    comando = "make";
    comando += (caminhoCompleto ? " && " + exec : " && ./" + exec);
  }

  // c++
  else if (tipo == ".cpp") {
    comando =
        (caminhoCompleto ? "g++ " + arquivo + " -o " + exec + "&& " + exec
                         : "g++ " + arquivo + " -o " + exec + "&& ./" + exec);

  }
  // c
  else if (tipo == ".c") {
    comando =
        (caminhoCompleto ? "gcc " + arquivo + " -o " + exec + "&& " + exec
                         : "gcc " + arquivo + " -o " + exec + "&& ./" + exec);
  }

  // rust
  else if (tipo == ".rs") {
    comando = "rustc " + arquivo + " && ./" + exec;
  }

  // java
  else if (tipo == ".java") {
    comando = "java " + arquivo;
  }

  // go
  else if (tipo == ".go") {
    comando = "go run " + arquivo;
  }

  // python
  else if (tipo == ".py") {
    comando = "python " + arquivo;
  }

  // javascript
  else if (tipo == ".js") {
    comando = "node " + arquivo;
  }

  // lua
  else if (tipo == ".lua") {
    comando = "lua " + arquivo;
  }

  // php
  else if (tipo == ".php") {
    comando = "php " + arquivo;
  }

  // bash
  else if (tipo == ".sh") {
    comando = "bash " + arquivo;
  }

  comando += addArgumentos(argc, argv);
  system(comando.c_str());

  return 0;
}
