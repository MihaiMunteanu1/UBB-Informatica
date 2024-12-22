from domeniu.nota import Note
from domeniu.notaDTO import NotaDTO
class NotaService:
    def __init__(self, repo_student, repo_lab, repo_nota,validator_nota,sort):
        self.__repo_student = repo_student
        self.__repo_lab = repo_lab
        self.__repo_nota = repo_nota
        self.__validator_nota = validator_nota
        self.__sort=sort

    def asignare_nota(self,nota_id, student_id, numar_problema,nota_asignata):

        self.__repo_student.cauta_student_dupa_id(student_id)
        self.__repo_lab.cauta_laborator_dupa_numar_problema(numar_problema)
        nota = NotaDTO(nota_id,student_id,numar_problema,nota_asignata)
        self.__validator_nota.validare_nota(nota)
        self.__repo_nota.add_nota(nota)
    def get_all_note(self):
        return self.__repo_nota.get_all()

    """def ordonare_dupa_note(self,numar_problema):
        self.__repo_lab.cauta_laborator_dupa_numar_problema(numar_problema)
        note_dtos = self.__repo_nota.get_all_nota_by_laborator(numar_problema)
        result = []
        for nota_dto in note_dtos:
            student = self.__repo_student.cauta_student_dupa_id(nota_dto.get_id_student())
            laborator = self.__repo_lab.cauta_laborator_dupa_numar_problema(nota_dto.get_id_laborator())
            nota = Note(nota_dto.get_id_nota(), student, laborator, nota_dto.get_nota())
            result.append(nota)

        result.sort(key=lambda x: x.get_nota())
        final_result = [(nota.get_student().get_nume(), nota.get_nota()) for nota in result]
        return final_result
    def ordonare_note_dupa_nume(self, numar_problema):
        self.__repo_lab.cauta_laborator_dupa_numar_problema(numar_problema)
        note_dtos = self.__repo_nota.get_all_nota_by_laborator(numar_problema)
        result = []

        for nota_dto in note_dtos:
            student = self.__repo_student.cauta_student_dupa_id(nota_dto.get_id_student())
            laborator = self.__repo_lab.cauta_laborator_dupa_numar_problema(nota_dto.get_id_laborator())
            nota = Note(nota_dto.get_id_nota(), student, laborator, nota_dto.get_nota())
            result.append(nota)

        result.sort(key=lambda x: x.get_student().get_nume())

        final_result = [(nota.get_student().get_nume(), nota.get_nota()) for nota in result]

        return final_result"""

    def ordonare_dupa_note(self, numar_problema):
        self.__repo_lab.cauta_laborator_dupa_numar_problema(numar_problema)
        note_dtos = self.__repo_nota.get_all_nota_by_laborator(numar_problema)
        result = []

        for nota_dto in note_dtos:
            student = self.__repo_student.cauta_student_dupa_id(nota_dto.get_id_student())
            laborator = self.__repo_lab.cauta_laborator_dupa_numar_problema(nota_dto.get_id_laborator())
            nota = Note(nota_dto.get_id_nota(), student, laborator, nota_dto.get_nota())
            result.append(nota)

        result = self.__sort.merge_sort(result, key=lambda x: x.get_nota())

        final_result = [(nota.get_student().get_nume(), nota.get_nota()) for nota in result]
        return final_result

    def ordonare_dupa_nota_si_nume(self, numar_problema):
        self.__repo_lab.cauta_laborator_dupa_numar_problema(numar_problema)
        note_dtos = self.__repo_nota.get_all_nota_by_laborator(numar_problema)
        result = []

        for nota_dto in note_dtos:
            student = self.__repo_student.cauta_student_dupa_id(nota_dto.get_id_student())
            laborator = self.__repo_lab.cauta_laborator_dupa_numar_problema(nota_dto.get_id_laborator())
            nota = Note(nota_dto.get_id_nota(), student, laborator, nota_dto.get_nota())
            result.append(nota)

        result = self.__sort.merge_sort(result, key=lambda x: x.get_nota(), compare=lambda x,
                                      y: -1 if x.get_student().get_nume() > y.get_student().get_nume() else 1)

        final_result = [(nota.get_student().get_nume(), nota.get_nota()) for nota in result]
        return final_result

    def ordonare_note_dupa_nume(self, numar_problema):
        self.__repo_lab.cauta_laborator_dupa_numar_problema(numar_problema)
        note_dtos = self.__repo_nota.get_all_nota_by_laborator(numar_problema)
        result = []

        for nota_dto in note_dtos:
            student = self.__repo_student.cauta_student_dupa_id(nota_dto.get_id_student())
            laborator = self.__repo_lab.cauta_laborator_dupa_numar_problema(nota_dto.get_id_laborator())
            nota = Note(nota_dto.get_id_nota(), student, laborator, nota_dto.get_nota())
            result.append(nota)

        self.__sort.bingo_sort(result, key=lambda x: x.get_student().get_nume())

        final_result = [(nota.get_student().get_nume(), nota.get_nota()) for nota in result]
        return final_result

    """
    Complexitatea de timp: Θ(n)
    Parcurge o singura data notele studentilor si adauga intr-o lista noua, notele studentilor care sunt egale cu 10
    
    """
    def studenti_cu_media_sub_5(self):
        note = self.__repo_nota.get_all_nota()
        medii_studenti = {}
        for nota in note:
            student_id = nota.get_id_student()
            nota_valoare = nota.get_nota()
            if student_id not in medii_studenti:
                medii_studenti[student_id] = {"suma_notelor": nota_valoare,
                                              "numar_note": 1}
            else:
                medii_studenti[student_id]["suma_notelor"] += nota_valoare
                medii_studenti[student_id]["numar_note"] += 1

        studenti_sub_5 = [{"nume": self.__repo_student.cauta_student_dupa_id(student_id).get_nume(),
                           "media": medii_studenti[student_id]["suma_notelor"] / medii_studenti[student_id][
                               "numar_note"]}
                          for student_id in medii_studenti if medii_studenti[student_id]["numar_note"] > 0 and
                          medii_studenti[student_id]["suma_notelor"] / medii_studenti[student_id]["numar_note"] < 5]
        return studenti_sub_5

    def studenti_cu_nota_10(self):
        note=self.__repo_nota.get_all_nota()
        studenti_10=[]
        for nota in note:
            if nota.get_nota()==10:
                student = self.__repo_student.cauta_student_dupa_id(nota.get_id_student())
                laborator = self.__repo_lab.cauta_laborator_dupa_numar_problema(nota.get_id_laborator())
                nota_10 = Note(nota.get_id_nota(), student, laborator, nota.get_nota())
                studenti_10.append(nota_10)

        final_result=[(nota.get_student().get_nume(), nota.get_nota()) for nota in studenti_10]
        return final_result