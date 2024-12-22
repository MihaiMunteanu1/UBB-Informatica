from domeniu.laborator import Laborator
class LaboratorRepository:
    def __init__(self):
        self._laboratoare = {}

    def add_laborator(self, laborator):
        numar_problema = laborator.get_numar_problema()
        if numar_problema in self._laboratoare:
            raise Exception("numar problema existent!\n")
        self._laboratoare[numar_problema] = laborator

    def get_all(self):
        return [self._laboratoare[x] for x in self._laboratoare.keys()]

    def sterge_laborator(self, numar_problema):
        if numar_problema in self._laboratoare:
            del self._laboratoare[numar_problema]
        else:
            raise Exception("Numar problema inexistent!\n")

    def modifica_laborator(self, laborator):
        numar_problema=laborator.get_numar_problema()
        if numar_problema in self._laboratoare:
            self._laboratoare[numar_problema]=laborator
        else:
            raise Exception("Numar problema inexistent!\n")

    def cauta_laborator_dupa_numar_problema(self, numar_problema):
        for numar_probl in self._laboratoare.keys():
            laborator = self._laboratoare[numar_probl]
            if laborator.get_numar_problema() == numar_problema:
                return laborator
        raise Exception("Nu exista laborator cu acest numar de problema")


class FileRepoLab(LaboratorRepository):

    def __init__(self, lab_file_path):
        LaboratorRepository.__init__(self)
        self.__lab_file_path = lab_file_path
    def __read_all_labs_from_file(self):
        with open(self.__lab_file_path, 'r') as f:
            self._laboratoare.clear()
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != '':
                    parti = line.split(',')
                    numar_problema = int(parti[0])
                    descriere = parti[1]
                    deadline = parti[2]
                    lab = Laborator(numar_problema, descriere, deadline)
                    self._laboratoare[numar_problema] = lab

    def __write_all_labs_to_file(self):
        with open(self.__lab_file_path, "w") as f:
            for nr_prob in self._laboratoare:
                f.write(str(self._laboratoare[nr_prob])+"\n")
    def __append_laborator_to_file(self, laborator):
        with open(self.__lab_file_path, 'a') as f:
            f.write(str(laborator) + '\n')

    def add_laborator(self, laborator):
        self.__read_all_labs_from_file()
        LaboratorRepository.add_laborator(self, laborator)
        self.__write_all_labs_to_file()

    def sterge_laborator(self, id_subject):
        self.__read_all_labs_from_file()
        LaboratorRepository.sterge_laborator(self,id_subject)
        self.__write_all_labs_to_file()
    def modifica_laborator_in_fisier(self, laborator):
        modified_lines = []
        with open(self.__lab_file_path, 'r') as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != '':
                    parti = line.split(',')
                    nr_prob = int(parti[0])
                    if nr_prob ==laborator.get_numar_problema():
                        modified_line = f"{nr_prob},{laborator.get_descriere()},{laborator.get_deadline()}\n"
                        modified_lines.append(modified_line)
                    else:
                        modified_lines.append(line)

        with open(self.__lab_file_path, 'w') as f:
            f.writelines(modified_lines)

    def modifica_laborator(self,laborator):
        self.__read_all_labs_from_file()
        LaboratorRepository.modifica_laborator(self,laborator)
        self.modifica_laborator_in_fisier(laborator)

    def cauta_laborator_dupa_numar_problema(self, numar_problema):
        with open(self.__lab_file_path, "r") as f:
            lines = f.readlines()
            for line in lines:
                if line != "":
                    parti = line.split(",")
                    current_nr_prob = int(parti[0])
                    if current_nr_prob == numar_problema:
                        descriere = parti[1]
                        deadline = parti[2]
                        return Laborator(current_nr_prob, descriere, deadline)
        raise Exception("numar problema inexistent în fisier")

    def get_all(self):
        self.__read_all_labs_from_file()
        return LaboratorRepository.get_all(self)