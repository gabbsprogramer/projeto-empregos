#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Definição da classe Funcionario
class Funcionario {
public:
    string nome; // Nome do funcionário
    string endereco; // Endereço do funcionário
    string CPF; // CPF do funcionário
    string dataAdmissao; // Data de admissão do funcionário
    string tipoFuncionario; // Tipo do funcionário (efetivo, temporário, estagiário)
    double salarioBase; // Salário base do funcionário
    int diasTrabalhados; // Número de dias trabalhados (apenas para funcionários temporários)
    double horasExtras; // Número de horas extras trabalhadas (apenas para funcionários efetivos)

    // Função para calcular o salário de um funcionário
    double calcularSalario() {
        double salario = 0;

        if (tipoFuncionario == "efetivo") {
            int horasExtras;
            cout << "Digite o número de horas extras trabalhadas: ";
            cin >> horasExtras;
            salario = salarioBase + horasExtras * 10; // Valor das horas extras é fixo em R$10 por hora
        }
        else if (tipoFuncionario == "temporario") {
            int diasTrabalhados;
            cout << "Digite o número de dias trabalhados: ";
            cin >> diasTrabalhados;
            salario = salarioBase * diasTrabalhados;
        }
        else if (tipoFuncionario == "estagiario") {
            salario = salarioBase; // Salário de estagiário é fixo de acordo com o salário mínimo
            // Exibição do salário líquido
            cout << "Nome do funcionário: " << nome << endl;
            cout << "Salário líquido: R$" << salario << endl;
            // Retornar sem realizar os cálculos de desconto
            return salario;
        }
        else {
            cout << "Tipo de funcionário inválido!" << endl;
            return salario;
        }

        // Desconto de INSS e Imposto de Renda
        double inss = salario * 0.1; // Desconto de 10% de INSS
        double ir = salario * 0.15; // Desconto de 15% de Imposto de Renda
        salario -= inss + ir;

        // Exibição do salário líquido
        cout << "Nome: " << nome << endl;
        cout << "Salário líquido: R$" << salario << endl;

        return salario;
    }
};

// Função para verificar a senha
bool verificarSenha() {
    string senha;
    cout << "\n===BEM VINDO AO SISTEMA DE CADASTRO DA EMPRESA AEROTINE INTERNATIONAL===\n";
    cout << "Digite a senha: ";
    cin >> senha;

    // Verifique se a senha é válida
    if (senha == "2022215973" || senha == "2022215628" || senha == "2022215882") {
        cout << "Senha correta. Acesso permitido." << endl;
        return true;
    } else {
        cout << "Senha incorreta. Acesso negado." << endl;
        return false;
    }
}

// Função para cadastrar um novo funcionário
void cadastrarFuncionario(vector<Funcionario>& funcionarios) {
    Funcionario novoFuncionario;

    cout << "Nome: " << endl;
    cin.ignore();
    getline(cin, novoFuncionario.nome);
    cout << "Endereco: ";
    getline(cin, novoFuncionario.endereco);
    cout << "CPF: ";
    getline(cin, novoFuncionario.CPF);
    cout << "Data de Admissao: ";
    getline(cin, novoFuncionario.dataAdmissao);
    cout << "Tipo de Funcionario (efetivo, temporario ou estagiario): ";
    getline(cin, novoFuncionario.tipoFuncionario);
    cout << "Salario Base: ";
    cin >> novoFuncionario.salarioBase;

    if (novoFuncionario.tipoFuncionario == "efetivo") {
        cout << "Horas Extras: ";
        cin >> novoFuncionario.horasExtras;
    }
    else if (novoFuncionario.tipoFuncionario == "temporario") {
        cout << "Dias Trabalhados: ";
        cin >> novoFuncionario.diasTrabalhados;
    }

    cin.ignore(); // Limpar o buffer do teclado antes de ler a próxima linha

    // Calcular o salário do funcionário
    double salario = novoFuncionario.calcularSalario();

    // Adicionar o funcionário ao vetor de funcionários
    funcionarios.push_back(novoFuncionario);

    cout << "Funcionario cadastrado com sucesso!" << endl;
    cout << "Salario: R$" << salario << endl;
}

// Função para editar o cadastro de um funcionário
void editarCadastro(vector<Funcionario>& funcionarios) {
    string cpf;
    cout << "CPF do funcionario a ser editado: ";
    cin.ignore();
    getline(cin, cpf);

    bool encontrado = false;
    for (Funcionario& funcionario : funcionarios) {
        if (funcionario.CPF == cpf) {
            cout << "Novo nome: ";
            getline(cin, funcionario.nome);
            cout << "Novo endereco: ";
            getline(cin, funcionario.endereco);
            cout << "Nova data de admissao: ";
            getline(cin, funcionario.dataAdmissao);

            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        cout << "Cadastro do funcionario atualizado com sucesso!" << endl;
    }
    else {
        cout << "Funcionario nao encontrado." << endl;
    }
}

// Função para gerar relatórios
void gerarRelatorios(const vector<Funcionario>& funcionarios) {
    cout << "Quantidade de Funcionarios Cadastrados: " << funcionarios.size() << endl;

    int quantidadeEfetivos = 0;
    int quantidadeTemporarios = 0;
    int quantidadeEstagiarios = 0;

    double totalSalariosEfetivos = 0;
    double totalSalariosTemporarios = 0;
    double totalSalariosEstagiarios = 0;

    for (const Funcionario& funcionario : funcionarios) {
        if (funcionario.tipoFuncionario == "efetivo") {
            quantidadeEfetivos++;
            totalSalariosEfetivos += funcionario.salarioBase;
        }
        else if (funcionario.tipoFuncionario == "temporario") {
            quantidadeTemporarios++;
            totalSalariosTemporarios += funcionario.salarioBase;
        }
        else if (funcionario.tipoFuncionario == "estagiario") {
            quantidadeEstagiarios++;
            totalSalariosEstagiarios += funcionario.salarioBase;
        }
    }

    double mediaSalarialEfetivos = quantidadeEfetivos > 0 ? totalSalariosEfetivos / quantidadeEfetivos : 0;
    double mediaSalarialTemporarios = quantidadeTemporarios > 0 ? totalSalariosTemporarios / quantidadeTemporarios : 0;
    double mediaSalarialEstagiarios = quantidadeEstagiarios > 0 ? totalSalariosEstagiarios / quantidadeEstagiarios : 0;


    cout << "Quantidade de Funcionarios Efetivos: " << quantidadeEfetivos << endl;
    cout << "Quantidade de Funcionarios Temporarios: " << quantidadeTemporarios << endl;
    cout << "Quantidade de Estagiarios: " << quantidadeEstagiarios << endl;

    cout << "Media Salarial dos Funcionarios Efetivos: R$" << mediaSalarialEfetivos << endl;
    cout << "Media Salarial dos Funcionarios Temporarios: R$" << mediaSalarialTemporarios << endl;
    cout << "Media Salarial dos Estagiarios: R$" << mediaSalarialEstagiarios << endl;

    double totalFolhaSalarial = totalSalariosEfetivos + totalSalariosTemporarios + totalSalariosEstagiarios;
    cout << "Valor Total da Folha Salarial da Empresa: R$" << totalFolhaSalarial << endl;
}

// Função para salvar os cadastros em um arquivo
void salvarCadastros(const vector<Funcionario>& funcionarios) {
    ofstream arquivo("cadastros.txt");

    if (arquivo.is_open()) {
        for (const Funcionario& funcionario : funcionarios) {
            arquivo << "Nome: " << funcionario.nome << endl;
            arquivo << "Endereco: " << funcionario.endereco << endl;
            arquivo << "CPF: " << funcionario.CPF << endl;
            arquivo << "Data de Admissao: " << funcionario.dataAdmissao << endl;
            arquivo << "Tipo de Funcionario: " << funcionario.tipoFuncionario << endl;
            arquivo << "Salario Base: " << funcionario.salarioBase << endl;

            if (funcionario.tipoFuncionario == "efetivo") {
                arquivo << "Horas Extras: " << funcionario.horasExtras << endl;
            }
            else if (funcionario.tipoFuncionario == "temporario") {
                arquivo << "Dias Trabalhados: " << funcionario.diasTrabalhados << endl;
            }

            arquivo << endl;
        }

        arquivo.close();
        cout << "Cadastros salvos com sucesso!" << endl;
    }
    else {
        cout << "Nao foi possivel abrir o arquivo para salvar os cadastros." << endl;
    }
}

// Função para carregar os cadastros de um arquivo
void carregarCadastros(vector<Funcionario>& funcionarios) {
    ifstream arquivo("cadastros.txt");

    if (arquivo.is_open()) {
        funcionarios.clear();

        string linha;
        Funcionario funcionario;

        while (getline(arquivo, linha)) {
            if (linha.find("Nome: ") != string::npos) {
                funcionario.nome = linha.substr(6);
            }
            else if (linha.find("Endereco: ") != string::npos) {
                funcionario.endereco = linha.substr(10);
            }
            else if (linha.find("CPF: ") != string::npos) {
                funcionario.CPF = linha.substr(5);
            }
            else if (linha.find("Data de Admissao: ") != string::npos) {
                funcionario.dataAdmissao = linha.substr(18);
            }
            else if (linha.find("Tipo de Funcionario: ") != string::npos) {
                funcionario.tipoFuncionario = linha.substr(21);
            }
            else if (linha.find("Salario Base: ") != string::npos) {
                funcionario.salarioBase = stod(linha.substr(14));
            }
            else if (linha.find("Horas Extras: ") != string::npos) {
                funcionario.horasExtras = stod(linha.substr(14));
            }
            else if (linha.find("Dias Trabalhados: ") != string::npos) {
                funcionario.diasTrabalhados = stoi(linha.substr(18));
                funcionarios.push_back(funcionario);
            }
        }

        arquivo.close();
        cout << "Cadastros carregados com sucesso!" << endl;
    }
    else {
        cout << "Nao foi possivel abrir o arquivo para carregar os cadastros." << endl;
    }
}

int main() {
    
// Verificar a senha antes de continuar
    if (!verificarSenha()) {
        return 0;  // Encerrar o programa se a senha estiver incorreta
    }
    
    vector<Funcionario> funcionarios; // Vetor para armazenar os funcionarios cadastrados
    int opcao;

    carregarCadastros(funcionarios);

    do {
        cout << endl;
        cout << "=== MENU ===" << endl;
        cout << "1. Cadastrar Funcionario" << endl;
        cout << "2. Editar Cadastro" << endl;
        cout << "3. Gerar Relatorios" << endl;
        cout << "4. Salvar Cadastros" << endl;
        cout << "0. Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrarFuncionario(funcionarios);
                break;
            case 2:
                editarCadastro(funcionarios);
                break;
            case 3:
                gerarRelatorios(funcionarios);
                break;
            case 4:
                salvarCadastros(funcionarios);
                break;
            case 0:
                break;
            default:
                cout << "Opcao invalida." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}
