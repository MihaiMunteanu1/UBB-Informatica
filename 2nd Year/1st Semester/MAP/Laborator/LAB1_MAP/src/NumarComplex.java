public class NumarComplex {

    private double re;
    private double im;

    public NumarComplex(double re, double im) {
        this.re = re;
        this.im = im;
    }

    public NumarComplex adunare(NumarComplex o){
        return new NumarComplex(o.re+this.re,this.im+ o.im);
    }

    public NumarComplex scadere(NumarComplex o){
        return new NumarComplex(this.re-o.re,this.im- o.im);
    }

    public NumarComplex inmultire(NumarComplex o){
        double re=this.re*o.re-this.im*o.im;
        double im=this.re*o.im+this.im*o.re;
        return new NumarComplex(re,im);
    }
/// (a+b*i)*(c+d*i) = (a*c-b*d)+(a*d+b*c)*i

    public NumarComplex impartire(NumarComplex o){
        double re = (this.re * o.re + this.im * o.im) / (o.re * o.re + o.im * o.im);
        double im = (o.re * this.im - this.re * o.re / (o.re * o.re + o.im * o.im));
        return new NumarComplex(re, im);
    }

/// (a+b*i)/(c+d*i) = (a*c+b*d)/(c*c+d*d)+(b*c-a*d)/(c*c+d*d)*i

    public NumarComplex conjugat(){
        return new NumarComplex(this.re,-this.im);
    }

    @Override
    public String toString() {
        return re + " + " + im+"*i";
    }

}
