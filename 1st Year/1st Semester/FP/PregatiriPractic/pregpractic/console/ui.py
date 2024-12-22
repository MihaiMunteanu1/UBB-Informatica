class UI:
    def __init__(self,service_examen):
        self.__service_examen=service_examen
        self.__comands={
            "print_examene":self.__ui_print_examene,
            "add_examen":self.__ui_adauga_examen,
            "data":self.__ui_examene_de_la_data,
            "export":self.__ui_export,
        }
    def __ui_export(self,params):
        if len(params)!=2:
            print("nr parametrii invalid")
            return
        try:
            nume_fisier=params[0]
            materia=params[1]
        except ValueError:
            raise Exception("parametru invalid")
        nume_fisier+='.txt'
        final_result=self.__service_examen.export(materia)
        with open(nume_fisier,'w') as f:
            for examen in final_result:
                f.write(str(examen)+"\n")
    def __ui_examene_de_la_data(self,params):
        if len(params)!=1:
            print("nr parametrii invalid")
            return
        try:
            data=params[0]
        except ValueError:
            raise Exception("parametru invalid")
        nr_data=int(data[:2])
        examene_de_la_data=self.__service_examen.examene_de_la_data(nr_data)
        for examen in examene_de_la_data:
            print(examen)

    def __ui_adauga_examen(self,params):
        if len(params)!=5:
            print("nr parametrii invalid")
            return
        try:
            id=int(params[0])
            data = params[1]
            ora = params[2]
            materia = params[3]
            tip = params[4]
        except ValueError:
            raise Exception("parametrii invalizi")

        self.__service_examen.add_examen(id,ora,data,materia,tip)
        print("examen adaugat cu succes!\n")

    def __functionalitate1(self):
        examene_de_maine=self.__service_examen.examene_de_maine()
        for examen in examene_de_maine:
            print(examen)
    def __ui_print_examene(self,params):
        if len(params)!=0:
            print("nr parametrii invalid")
            return
        examane=self.__service_examen.get_all()
        for examen in examane:
            print(f"{examen.get_id()}, {examen.get_data()}, {examen.get_ora()}, {examen.get_materia()}, {examen.get_tip()}")

    def run(self):
        self.__functionalitate1()
        while True:
            cmd=input(">>>")
            cmd=cmd.strip()
            if cmd=='exit':
                return
            parti=cmd.split(' ')
            nume=parti[0]
            params=parti[1:]
            if nume in self.__comands:
                try:
                    self.__comands[nume](params)
                except Exception as ex:
                    print(ex)
            else:
                print("Comanda invalida")
