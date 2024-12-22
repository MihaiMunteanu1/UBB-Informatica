class UI:
    def __init__(self,service_student,service_laborator,service_nota):
        self.__service_student=service_student
        self.__service_laborator=service_laborator
        self.__service_nota=service_nota
        self.__commands={
            "add_student":self.__add_student,
            "add_laborator":self.__add_laborator,
            "print_student":self.__print_student,
            "print_laborator":self.__print_laborator,
            "sterge_student":self.__sterge_student,
            "sterge_laborator":self.__sterge_laborator,
            "modifica_student":self.__modifica_student,
            "modifica_laborator":self.__modifica_laborator,
            "cauta_student_dupa_id":self.__cauta_student_dupa_id,
            "cauta_laborator_dupa_numar_problema":self.__cauta_laborator_dupa_numar_problema,
            "adauga_studenti_random":self.__ui_adauga_studenti_random,
            "asignare_nota":self.__ui_asignare_nota,
            "print_nota":self.__ui_print_nota,
            "ordonare_studenti_dupa_nume_la_lab": self.__ui_ordonare_note_nume,
            "ordonare_studenti_dupa_note_la_lab": self.__ui_ordonare_dupa_note,
            "studenti_cu_media_sub_5": self.__ui_media_sub_5,
            "studenti_cu_nota_10": self.__ui_studenti_cu_nota_10,
        }
    def __ui_studenti_cu_nota_10(self,params):
        if len(params) != 0:
            print("nr parametrii invalid!")
            return
        studenti=self.__service_nota.studenti_cu_nota_10()
        if len(studenti)==0:
            raise Exception("nu exista studenti cu nota 10")
        for nume,nota in studenti:
            print(f"Nume: {nume} cu nota: {nota}")
    def __ui_media_sub_5(self,params):
        if len(params)!=0:
            print("nr parametrii invalid!")
            return
        studenti = self.__service_nota.studenti_cu_media_sub_5()
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
        note_filtrate = self.__service_nota.ordonare_dupa_note(numar_problema)
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
        note_filtrate= self.__service_nota.ordonare_note_dupa_nume(numar_problema)
        if len(note_filtrate) == 0:
            raise Exception("nu exista note")
        for nume,nota in note_filtrate:
            print(f"Nume: {nume} cu nota: {nota}")
    def __ui_print_nota(self,params):
        if len(params)!=0:
            raise Exception("nr parametrii invalid")
            return
        note=self.__service_nota.get_all()
        for nota in note:
            print(nota)
    def __ui_asignare_nota(self,params):
        if len(params)!=4:
            raise Exception("nr parametrii invalid")
            return
        try:
            id_nota=int(params[0])
            id_student=int(params[1])
            id_lab=int(params[2])
            val_nota=int(params[3])
        except ValueError:
            raise Exception("valoari numerica invalide")
        self.__service_nota.add_nota(id_nota,id_student,id_lab,val_nota)
        print("nota asignata cu succes")

    def __ui_adauga_studenti_random(self,params):
        if len(params)!=1:
            raise Exception("nr parametrii invalid")
            return
        try:
            nr_studenti=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__service_student.adauga_studenti_random(nr_studenti)
        print("studenti adaugati cu succes")

    def __cauta_student_dupa_id(self,params):
        if len(params)!=1:
            raise Exception("nr parametrii invalid")
            return
        try:
            id_student=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        stundet_cautat=self.__service_student.cauta_student_dupa_id(id_student)
        print(f"id:{stundet_cautat.get_id_student()}, nume: {stundet_cautat.get_nume()}, grup:{stundet_cautat.get_grup()}")
    def __cauta_laborator_dupa_numar_problema(self,params):
        if len(params) != 1:
            raise Exception("nr parametrii invalid")
            return
        try:
            numar_problema = int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        lab_cautat = self.__service_laborator.cauta_laborator_dupa_numar_problema(numar_problema)
        print(f"numar problema: {lab_cautat.get_numar_problema()}, descriere:{lab_cautat.get_descriere()}, deadline:{lab_cautat.get_deadline()}")
    def __modifica_laborator(self,params):
        if len(params) != 3:
            raise Exception("nr parametrii invalid")
            return
        try:
            numar_problema = int(params[0])
            descriere = params[1]
            deadline = params[2]
        except ValueError:
            raise Exception("valori invalide")
        self.__service_laborator.modifica_laborator(numar_problema,descriere,deadline)
        print("laborator modificat cu succes")
    def __modifica_student(self,params):
        if len(params)!=3:
            raise Exception("nr parametrii invalid")
            return
        try:
            id_student=int(params[0])
            nume=params[1]
            grup=int(params[2])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__service_student.modifica_student(id_student,nume,grup)
        print("student modifica cu succes")

    def __sterge_student(self,params):
        if len(params)!=1:
            raise Exception("nr parametrii invalid")
            return
        try:
            id_student=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__service_student.sterge_student(id_student)
        print("student sters cu succes")

    def __sterge_laborator(self,params):
        if len(params)!=1:
            raise Exception("nr parametrii invalid")
            return
        try:
            numar_problema=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__service_laborator.sterge_laborator(numar_problema)
        print("laborator sters cu succes")

    def __print_student(self,params):
        if len(params)!=0:
            raise Exception("nr parametrii invalid")
            return
        studenti=self.__service_student.get_all()
        for student in studenti:
            print(student)

    def __print_laborator(self,params):
        if len(params) != 0:
            raise Exception("nr parametrii invalid")
            return
        laboratoare=self.__service_laborator.get_all()
        for laborator in laboratoare:
            print(laborator)
    def __add_student(self,params):
        if len(params)!=3:
            raise Exception("nr parametrii invalid")
            return
        try:
            id_student=int(params[0])
            nume=params[1]
            grup=int(params[2])
        except ValueError:
            raise Exception("valori invalide")
        self.__service_student.add_student(id_student,nume,grup)
        print("student adaugat cu succes")
    def __add_laborator(self,params):
        if len(params) != 3:
            raise Exception("nr parametrii invalid")
            return
        try:
            numar_problema = int(params[0])
            descriere = params[1]
            deadline = params[2]
        except ValueError:
            raise Exception("valori invalide")
        self.__service_laborator.add_laborator(numar_problema,descriere,deadline)
        print("laborator adaugat cu succes")
    def run(self):
        while True:
            cmd = input(">>>")
            cmd = cmd.strip()
            if cmd == "exit":
                return
            parts = cmd.split(" ")
            cmd_name = parts[0]
            params = parts[1:]
            if cmd_name in self.__commands:
                try:
                    self.__commands[cmd_name](params)
                except Exception as ex:
                    print(ex)
            else:
                print("comanda invalida!")