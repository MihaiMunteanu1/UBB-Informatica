from domain.piesa import Piesa
class FileRepoPiese:
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier
        self.__piese={}
    def __read_all_from_file(self):
        with open(self.__cale_fisier,'r') as f:
            self.__piese.clear()
            lines=f.readlines()
            for line in lines:
                line=line.strip()
                if line!='':
                    parti=line.split(',')
                    id=int(parti[0])
                    titlu=parti[1]
                    regizor=parti[2]
                    gen=parti[3]
                    durata=int(parti[4])
                    piesa=Piesa(id,titlu,regizor,gen,durata)
                    self.__piese[id]=piesa

    def __write_all_to_file(self):
        with open(self.__cale_fisier,'w') as f:
            for id in self.__piese:
                f.write(str(self.__piese[id])+'\n')
    def add_piesa(self,piesa):
        self.__read_all_from_file()
        id_piesa=piesa.get_id()
        if id_piesa in self.__piese:
            raise Exception("id existent")
        else:
            self.__piese[id_piesa]=piesa
        self.__write_all_to_file()
        self.__read_all_from_file()

    def modifica(self,titlu,regizor,new_gen,new_durata):
        self.__read_all_from_file()
        piese=self.get_all()
        ok=int(0)
        for piesa in piese:
            if piesa.get_titlu()==titlu and piesa.get_regizor()==regizor:
                piesa.set_durata(new_durata)
                piesa.set_gen(new_gen)
                ok=1

        if ok:
            self.__write_all_to_file()
        else:
            raise Exception("nu exista piesa cu acest titlu/regizor")


    def get_all(self):
        self.__read_all_from_file()
        return [self.__piese[x] for x in self.__piese.keys()]