#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// essa função adiciona os argumentos passados para o programa
string addArgumentos(int argc, vector<string> argumentos) {
  string co;
  if (argc > 2) {
    for (int i = 0; i < argumentos.size(); i++) {
      co += string(" ") + argumentos[i];
    }
  }
  return co;
}

// função principal do programa
int main(int argc, char *argv[]) {
  string tipo = "n";
  vector<string> argumentos;
  string arquivo;
  if (argc > 1) {
    arquivo = argv[1];
    // verifica tipo do arquivo
    string exts[] = {".cpp", ".py", ".sh", ".c"};
    size_t ext;
    for (size_t i = 0; i < sizeof(exts) / sizeof(exts[0]); ++i) {
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

  // verifica se existem outros argumentos
  if (argc > 2) {
    for (int i = 2; i < argc; i++) {
      argumentos.push_back(argv[i]);
    }
  }

  // remover a extenção.
  size_t ponto = arquivo.find(".");
  string exec = arquivo.substr(0, ponto);

  bool caminhoCompleto = false;
  size_t dir = arquivo.rfind("/");

  if (dir != string::npos) {
    caminhoCompleto = true;
  }

  // c++
  if (tipo == ".cpp") {
    string comando;
    // caminho completo
    if (caminhoCompleto) {
      comando =
          string("g++ ") + arquivo + string(" -o ") + exec + " && " + exec;
    } else {  // caminho relativo
      comando =
          string("g++ ") + arquivo + string(" -o ") + exec + " && ./" + exec;
    }

    comando += addArgumentos(argc, argumentos);

    system(comando.c_str());
  }
  // c
  else if (tipo == ".c") {
    string comando;
    // caminho completo
    if (caminhoCompleto) {
      comando =
          string("gcc ") + arquivo + string(" -o ") + exec + " && " + exec;
    } else {  // caminho relativo
      comando =
          string("gcc ") + arquivo + string(" -o ") + exec + " && ./" + exec;
    }

    comando += addArgumentos(argc, argumentos);

    system(comando.c_str());
  }
  // python
  else if (tipo == ".py") {
    string comando = string("python ") + arquivo;
    comando += addArgumentos(argc, argumentos);
    system(comando.c_str());
  }

  // bash
  else if (tipo == ".sh") {
    string comando = string("bash ") + arquivo;
    comando += addArgumentos(argc, argumentos);
    system(comando.c_str());
  }

  return 0;
}
