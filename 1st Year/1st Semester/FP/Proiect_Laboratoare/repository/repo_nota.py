from domeniu.notaDTO import NotaDTO
class NotaRepository:
    def __init__(self):
        self.__nota_list={}

    def add_nota(self, nota):
        id_nota = nota.get_id_nota()
        id_student = nota.get_id_student()
        id_lab = nota.get_id_laborator()
        if id_nota in self.__nota_list:
            raise Exception("id nota existenta")
        toate_note = self.get_all()
        for note in toate_note:
            if note.get_id_student() == id_student:
                if note.get_id_laborator() == id_lab:
                    raise Exception("studentul are deja nota la aceasta problema")
        self.__nota_list[id_nota] = nota
    def get_all_nota_by_laborator(self, numar_problema):
        return [nota for nota in self.__nota_list.values() if nota.get_id_laborator() == numar_problema]

    def get_all(self):
        return [self.__nota_list[x] for x in self.__nota_list.keys()]
