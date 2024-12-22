
class UI:
    def __init__(self,service_studentz,service_laboratoare,service_note):
        self.__service_studentz = service_studentz
        self.__service_laboratoare = service_laboratoare
        self.__service_note = service_note
        self.__commandz = {
            "adauga_student":self.__ui_add_student,
            "adauga_laborator":self.__ui_add_laborator,
            "print_studenti":self.__ui_print_students,
            "print_laborator":self.__ui_print_laboratoare,
            "sterge_student":self.__ui_sterge_student,
            "sterge_laborator":self.__ui_sterge_laborator,
            "modifica_student":self.__ui_modifica_student,
            "modifica_laborator":self.__ui_modifica_laborator,
            "cauta_student_dupa_id":self.__ui_cauta_student_dupa_id,
            "cauta_laborator_dupa_numar_problema":self.__ui_cauta_laborator_dupa_numar_problema,
            "adauga_student_random":self.__ui_adauga_student_random,
            "asignare_nota":self.__ui_asignare_nota,
            "print_note":self.__ui_print_note,
            "ordonare_studenti_dupa_nume_la_lab":self.__ui_ordonare_note_nume,
            "ordonare_studenti_dupa_note_la_lab":self.__ui_ordonare_dupa_note,
            "studenti_cu_media_sub_5":self.__ui_media_sub_5,
            "studenti_cu_nota_10":self.__ui_studenti_cu_nota_10,
        }
    def __ui_studenti_cu_nota_10(self,params):
        if len(params) != 0:
            print("nr parametrii invalid!")
            return
        studenti=self.__service_note.studenti_cu_nota_10()
        if len(studenti)==0:
            raise Exception("nu exista studenti cu nota 10")
        for nume,nota in studenti:
            print(f"Nume: {nume} cu nota: {nota}")
    def __ui_media_sub_5(self,params):
        if len(params)!=0:
            print("nr parametrii invalid!")
            return
        studenti = self.__service_note.studenti_cu_media_sub_5()
        if len(studenti)==0:
            raise Exception("nu exista medii sub 5")
        for student in studenti:
            print(f"{student['nume']}: {student['media']}")
    def __ui_ordonare_dupa_note(self,params):
        if len(params)!=1:
            print("nr parametrii invalid!")
            return
        try:
            numar_problema = int(params[0])
        except ValueError:
            raise Exception("parametru invalid")
        note_filtrate = self.__service_note.ordonare_dupa_nota_si_nume(numar_problema)
        if len(note_filtrate) == 0:
            raise Exception("nu exista note")
        for nume, nota in note_filtrate:
            print(f"Nume: {nume} cu nota: {nota}")
    def __ui_ordonare_note_nume(self,params):
        if len(params)!= 1:
            print("nr parametrii invalid!")
            return
        try:
            numar_problema=int(params[0])
        except ValueError:
            raise Exception("parametru invalid")
        note_filtrate= self.__service_note.ordonare_note_dupa_nume(numar_problema)
        if len(note_filtrate) == 0:
            raise Exception("nu exista note")
        for nume,nota in note_filtrate:
            print(f"Nume: {nume} cu nota: {nota}")


    def __ui_print_note(self,params):
        if len(params)!=0:
            print("nr parametrii invalid!")
            return
        note = self.__service_note.get_all_note()
        if len(note) == 0:
            raise Exception("nu exista note")
        for nota in note:
            print(nota)

    def __ui_asignare_nota(self, params):
        if len(params) != 4:
            print("nr parametrii invalid!")
            return
        try:
            id_nota = int(params[0])
            student_id = int(params[1])
            lab_id = int(params[2])
            nota = float(params[3])
        except ValueError:
            raise Exception("parametrii invalizi!")
        self.__service_note.asignare_nota(id_nota,student_id,lab_id,nota)
        print("nota asignata!")
    def __ui_adauga_student_random(self,params):
        if len(params)!=1:
            print("nr parametrii invalid")
            return
        try:
            numar=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__service_studentz.generate_student(numar)
        print("student/studenti adaugat cu succes!")

    def __ui_cauta_laborator_dupa_numar_problema(self,params):
        if len(params)!=1:
            print("nr parametrii invalid")
            return
        try:
            numar_problema=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        laborator=self.__service_laboratoare.cauta_laborator_dupa_numar_problema(numar_problema)
        print(f"Numar problema: {laborator.get_numar_problema()}, Descriere: {laborator.get_descriere()}, Data deadline: {laborator.get_deadline()}")

    def __ui_cauta_student_dupa_id(self,params):
        if len(params)!=1:
            print("nr parametrii invalid")
            return
        try:
            studentID=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")

        student=self.__service_studentz.cauta_student_dupa_id(studentID,0)
        print(f"ID: {student.get_studentid()}, Nume: {student.get_nume()}, Grup: {student.get_grup()}")



    def __ui_modifica_student(self,params):
        if len(params)!=3:
            print("nr parametrii invalid")
            return
        try:
            studentID=int(params[0])
            new_nume=params[1]
            new_grup=int(params[2])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__service_studentz.modifica_student(studentID,new_nume, new_grup)
        print("student modificat cu succes")

    def __ui_modifica_laborator(self,params):
        if len(params)!=3:
            print("nr parametrii invalid")
            return
        try:
            numar_problema=int(params[0])
            descriere=params[1]
            deadline=params[2]
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__service_laboratoare.modifica_laborator(numar_problema,descriere,deadline)
        print("laborator modificat cu succes")
    def __ui_sterge_student(self,params):
        if len(params)!=1:
            print("nr parametrii invalid")
            return
        try:
            studentID=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__service_studentz.sterge_student(studentID)
        print("student sters cu succes")

    def __ui_sterge_laborator(self,params):
        if len(params)!=1:
            print("nr parametrii invalid")
            return
        try:
            numar_problema=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__service_laboratoare.sterge_laborator(numar_problema)
        print("problema stearsa cu succes")

    def __ui_print_students(self,params):
        if len(params)!=0:
            print("nr parametri invalid!")
            return
        studentz = self.__service_studentz.get_all_students()
        for student in studentz:
            print(student)
    def __ui_add_student(self,params):
        if len(params)!=3:
            print("nr parametri invalid!")
            return
        try:
            studentID = int(params[0])
            nume = params[1]
            grup = int(params[2])
        except ValueError:
            raise Exception("valoare numerica invalida!")
        self.__service_studentz.add_student(studentID,nume, grup)
        print("student adaugat cu succes!")

    def __ui_print_laboratoare(self, params):
        if len(params) != 0:
            print("nr parametri invalid!")
            return
        laboratoare = self.__service_laboratoare.get_all_laboratoare()
        for laborator in laboratoare:
            print(laborator)

    def __ui_add_laborator(self, params):
        if len(params) != 3:
            print("nr parametri invalid!")
            return
        try:
            numar_problema = int(params[0])
            descriere = params[1]
            deadline = params[2]
        except ValueError:
            raise Exception("valoare numerica invalida!")
        self.__service_laboratoare.add_laborator(numar_problema, descriere, deadline)
        print("laborator adaugat cu succes!")

    def run(self):
        while True:
            cmd = input(">>>")
            cmd = cmd.strip()
            if cmd == "exit":
                return
            parts = cmd.split(" ")
            cmd_name = parts[0]
            params = parts[1:]
            if cmd_name in self.__commandz:
                try:
                    self.__commandz[cmd_name](params)
                except Exception as ex:
                    print(ex)
            else:
                print("comanda invalida!")