#pragma once
#include <string>
#include <iostream>
#include <utility>
using std::cout;
using std::string;
using std::exception;
class ActivitateException : public exception{
    string msg;
public:
    explicit ActivitateException(string msg) : msg{std::move(msg)} {
    }
    [[nodiscard]] string get_msg() const {
        return msg;
    }
};
class  Activitate {
private:
    string titlu;
    string descriere;
    string tip;
    int durata;
public:
    [[nodiscard]] string get_titlu() const;
    [[nodiscard]] string get_descriere() const;
    [[nodiscard]] string get_tip() const;
    [[nodiscard]] int get_durata() const;
    Activitate()=default;
    /**
     * Constructor pentru clasa Activitate.
     * @param titlu
     * @param descriere
     * @param tip
     * @param durata
     */
    Activitate(string titlu, string descriere,string tip,int durata): titlu{std::move(titlu)},descriere{std::move(descriere)},tip{std::move(tip)},durata{durata}{
        ///cout<<"constructor\n";
    }

    /**
     * Destructor pentru clasa Activitate.
     */
    ~Activitate(){
        ///cout<<"destructor\n";
    }

    /**
     * Constructor de copiere pentru clasa Activitate.
     * @param ot
     */
    Activitate(const Activitate& ot): titlu{ot.titlu},descriere{ot.descriere},tip{ot.tip},durata{ot.durata}{
        ///cout<<"copy constructor\n";
    }

    Activitate& operator=(const Activitate& ot)=default;

};