from domeniu.notaDTO import NotaDTO
class NotaRepository:
    def __init__(self):
        self._nota_list={}
    def add_nota(self,nota):
        id_nota=nota.get_id_nota()
        id_student=nota.get_id_student()
        id_lab=nota.get_id_laborator()
        if id_nota in self._nota_list:
            raise Exception("id nota existenta")
        toate_note=self.get_all_nota()
        for note in toate_note:
            if note.get_id_student() == id_student:
                if note.get_id_laborator()==id_lab:
                    raise Exception("studentul are deja nota la aceasta problema")
        self._nota_list[id_nota] = nota

    def get_all_nota(self):
        return [self._nota_list[x] for x in self._nota_list.keys()]

    def get_all_nota_by_laborator(self, numar_problema):
        return [nota for nota in self._nota_list.values() if nota.get_id_laborator() == numar_problema]

    def __len__(self):
        return len(self._nota_list)


class FileNotaRepository(NotaRepository):
    def __init__(self, note_file_path):
        NotaRepository.__init__(self)
        self.__note_file_path = note_file_path

    def __read_all_note_from_file(self):
        with open(self.__note_file_path, 'r') as f:
            self._nota_list.clear()
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != '':
                    parti = line.split(',')
                    id_nota = int(parti[0])
                    id_student = int(parti[1])
                    id_lab = int(parti[2])
                    valoare_nota = float(parti[3])
                    notaDTO = NotaDTO(id_nota, id_student, id_lab, valoare_nota)
                    self._nota_list[id_nota] = notaDTO
    def __write_all_note_to_file(self):
        with open(self.__note_file_path, "w") as f:
            for id_nota in self._nota_list:
                f.write(str(self._nota_list[id_nota])+"\n")
    def __append_nota_to_file(self, nota):
        with open(self.__note_file_path, 'a') as f:
            f.write(str(nota) + '\n')

    def add_nota(self, nota):
        self.__read_all_note_from_file()
        NotaRepository.add_nota(self, nota)
        self.__write_all_note_to_file()

    def __len__(self):
        self.__read_all_note_from_file()
        return NotaRepository.__len__(self)

    def get_all(self):
        self.__read_all_note_from_file()
        return NotaRepository.get_all_nota(self)