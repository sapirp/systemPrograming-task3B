#include<iostream>
#include "solver.hpp"

using namespace solver;
using namespace std;


double RealVariable::solveEquation(RealVariable& eq){
    if(eq.a==0 && eq.b==0) throw std::exception();

    if(!eq.power){
        return -eq.c/eq.b;
    }
    else{ 
        double SquareRoot = eq.b*eq.b - 4*eq.a*eq.c;
        double solveEq;
        if(SquareRoot>=0) { 
            solveEq = (-eq.b + sqrt(SquareRoot)) / (2*eq.a);
        }
        else {
            throw std::exception();
        }
        return solveEq;
        }
}

double solver::solve(RealVariable& eq){
    return eq.solveEquation(eq);   
}

RealVariable& RealVariable::copy (RealVariable& rv){
    this->a=rv.a;
    this->b=rv.b;
    this->c=rv.c;
    this->power=rv.power;  
    return *this;
}

//opertor +
RealVariable& solver::operator+ (RealVariable& rv , double num){
    RealVariable *rvCopy= new RealVariable();
    rvCopy->copy(rv);
    rvCopy->c=rv.c+num;
    return *rvCopy;
}

RealVariable& solver::operator+ (double num , RealVariable& rv){
    return (rv + num);
}

RealVariable& solver::operator+ (RealVariable& rv1 , RealVariable& rv2){
    RealVariable* rvCopy=new RealVariable();    
    rvCopy->a=rv1.a+rv2.a;
    rvCopy->b=rv1.b+rv2.b;
    rvCopy->c=rv1.c+rv2.c;
    rvCopy->power= rv1.power? rv1.power : rv2.power;
    return *rvCopy;
}

//opertor -
RealVariable& solver::operator- (RealVariable& rv , double num){
    RealVariable* rvCopy=new RealVariable();
    rvCopy->copy(rv);
    rvCopy->c=rv.c-num; 
    return *rvCopy;
}

RealVariable& solver::operator- (double num , RealVariable& rv){
    return (rv - num);
}

RealVariable& solver::operator- (RealVariable& rv1 , RealVariable& rv2){
    RealVariable* rvCopy=new RealVariable();  
    rvCopy->a=rv1.a-rv2.a;
    rvCopy->b=rv1.b-rv2.b;
    rvCopy->c=rv1.c-rv2.c;
    rvCopy->power = rv1.power ? rv1.power : rv2.power;
    return *rvCopy;
}

//opertor *
RealVariable& solver::operator* (RealVariable& rv , double num){
    return (num * rv);
}

RealVariable& solver::operator* (double num , RealVariable& rv){
    cout<< "op * : a=" << rv.a <<" b=" << rv.b <<"c="<<rv.c<<endl;
    RealVariable* rvCopy=new RealVariable();
    rvCopy->copy(rv);
    if(rv.power) {
        rvCopy->a*=num;
    }
    else if(rv.b==0){
      rvCopy->b=num;
    }
    else rvCopy->b*=num;
    return *rvCopy;
}

RealVariable& solver::operator* (RealVariable& rv1 , RealVariable& rv2){
    if(rv1.power || rv2.power) throw std::exception();
    
    RealVariable *rvCopy= new RealVariable();
    rvCopy->copy(rv1);

    if(rv1.a != 0 && rv2.a !=0) rvCopy->a=rv1.a*rv2.a;
    rvCopy->a=rv1.a+rv2.a;
    rvCopy->power=true;
    
    return *rvCopy;   
}

//opertor /
RealVariable& solver::operator/ (RealVariable& rv , double num){
    if(num==0) throw std::exception();

    RealVariable *rvCopy= new RealVariable();
    rvCopy->a=rv.a/num;
    rvCopy->b=rv.b/num;
    rvCopy->c=rv.c/num;
    rvCopy->power=rv.power;
    return *rvCopy;
}

RealVariable& solver::operator/ (double num , RealVariable& rv){
    RealVariable *rvCopy= new RealVariable();
    rvCopy->a=num/rv.a;
    rvCopy->b=num/rv.b;
    rvCopy->c=num/rv.c;
    rvCopy->power=rv.power;
    return *rvCopy;
}

//operator ^
RealVariable& solver::operator^ (RealVariable& rv, const int num){
    if (num != 2 || rv.power) throw std::exception();
    RealVariable *rvCopy= new RealVariable();
    rvCopy->copy(rv);
    rvCopy->a=rv.b;
    rvCopy->power=true;
    rvCopy->b=0;
    return *rvCopy;
}

//opertor ==
RealVariable& solver::operator== (RealVariable& rv , double num){
    RealVariable *rvCopy= new RealVariable();
    rvCopy->copy(rv);
    if(num>0) rvCopy->c-=num;
    else rvCopy->c+=-num;
    return *rvCopy;
}

RealVariable& solver::operator== (double num , RealVariable& rv){
    cout<< "operator ==: a=" << rv.a << "b=" <<rv.b <<"c=" << rv.c<< endl;
    return (rv == num);
}

RealVariable& solver::operator== (RealVariable& rv1 , RealVariable& rv2){
    RealVariable* rvCopy = new RealVariable();
    *rvCopy=rv1-rv2;
    return *rvCopy;
}

//complex variable
std::complex<double> ComplexVariable::solveEquation(ComplexVariable& eq){

if(eq.a==std::complex<double>(0.0,0.0) && eq.b==std::complex<double>(0.0,0.0)) throw std::exception();
    if(!eq.power){
        return -eq.c/eq.b;
    }
    if (eq.b==std::complex<double>(0.0,0.0) && power){
        std::complex<double> c=-eq.c/eq.a;
        return sqrt(c);
    }
    else{
        std::complex<double> SquareRoot = sqrt(eq.b*eq.b - 4.0 *eq.a*eq.c);
        std::complex<double> solveEq= (-eq.b + SquareRoot) / (2.0*eq.a);
    return solveEq;
    }
}

 std::complex<double> solver::solve(ComplexVariable& eq){
     return eq.solveEquation(eq);
 }

ComplexVariable& ComplexVariable::copy (ComplexVariable& cv){
        this->a=cv.a;
        this->b=cv.b;
        this->c=cv.c;
        this->power=cv.power;
        
        return *this;
}

//operator +
ComplexVariable& solver::operator+ (ComplexVariable& cv , complex<double> num){
    ComplexVariable *cvCopy= new ComplexVariable();
    cvCopy->copy(cv);
    cvCopy->c=cv.c+num; 
    return *cvCopy;
}

ComplexVariable& solver::operator+ (complex<double> num, ComplexVariable& cv ){
    return (cv + num);
}

ComplexVariable& solver::operator+ (ComplexVariable& cv1, ComplexVariable& cv2 ){
    ComplexVariable* cvCopy=new ComplexVariable();
         
    cvCopy->a=cv1.a+cv2.a;
    cvCopy->b=cv1.b+cv2.b;
    cvCopy->c=cv1.c+cv2.c;
    cvCopy->power=cv1.power? cv1.power : cv2.power;
    return *cvCopy;
}


//operator -
ComplexVariable& solver::operator- (ComplexVariable& cv , complex<double> num){
    ComplexVariable *cvCopy= new ComplexVariable();
    cvCopy->copy(cv);
    cvCopy->c=cv.c-num;
    return *cvCopy;
}

ComplexVariable& solver::operator- (complex<double> num, ComplexVariable& cv ){
    return (cv - num);
}

ComplexVariable& solver::operator- (ComplexVariable& cv1, ComplexVariable& cv2 ){
    ComplexVariable* cvCopy=new ComplexVariable();
    cvCopy->a=cv1.a-cv2.a;
    cvCopy->b=cv1.b-cv2.b;
    cvCopy->c=cv1.c-cv2.c;
    cvCopy->power = cv1.power ? cv1.power : cv2.power;
    return *cvCopy;
}

//operator *

ComplexVariable& solver::operator* (ComplexVariable& cv1, ComplexVariable& cv2 ){
    if(cv1.power || cv2.power) throw std::exception();
    
    ComplexVariable *cvCopy= new ComplexVariable();
    cvCopy->copy(cv1);

    if(cv1.a != std::complex(0.0,0.0) && cv2.a !=std::complex(0.0,0.0)) cvCopy->a=cv1.a*cv2.a;
    cvCopy->a=cv1.a+cv2.a;
    cvCopy->power=true;
    
    return *cvCopy;
}

ComplexVariable& solver::operator* (complex<double> c , ComplexVariable& cv ){
    ComplexVariable* cvCopy=new ComplexVariable();
    cvCopy->copy(cv);
    if(cv.power) {
        cvCopy->a*=c;
    }
    else if(cv.b==std::complex(0.0,0.0)){
        cvCopy->b=c;
    }
    else cvCopy->b*=c;

    return *cvCopy;
}

ComplexVariable& solver::operator* (ComplexVariable& cv , complex<double> c ){
    return (c * cv);
}

//operator /

ComplexVariable& solver::operator/ (complex<double> c , ComplexVariable& cv ){
    ComplexVariable *cvCopy= new ComplexVariable();
    cvCopy->a=c/cv.a;
    cvCopy->b=c/cv.b;
    cvCopy->c=c/cv.c;
    cvCopy->power=cv.power;
    return *cvCopy;
}

ComplexVariable& solver::operator/ (ComplexVariable& cv , complex<double> c ){
    ComplexVariable *cvCopy= new ComplexVariable();
    cvCopy->a=cv.a/c;
    cvCopy->b=cv.b/c;
    cvCopy->c=cv.c/c;
    cvCopy->power=cv.power;
    return *cvCopy;
}

ComplexVariable& solver::operator^ (ComplexVariable& cv, const int num){
    if (num != 2) throw std::exception();
    ComplexVariable *cvCopy= new ComplexVariable();
    cvCopy->copy(cv);
    cvCopy->a=cv.b;
    cvCopy->b=std::complex<double>(0.0,0.0);;
    cvCopy->power=true;
    
    return *cvCopy;
}

//operator ==
ComplexVariable& solver::operator== (ComplexVariable& cv , double num){
    ComplexVariable *cvCopy= new ComplexVariable();
    cvCopy->copy(cv);
    if(num>0) cvCopy->c-=num;
    else cvCopy->c+=-num;
    return *cvCopy;
}

ComplexVariable& solver::operator== (double num, ComplexVariable& cv ){
    return (cv == num);
}

ComplexVariable& solver::operator== (ComplexVariable& cv1, ComplexVariable& cv2 ){
    ComplexVariable* cvCopy = new ComplexVariable();
    *cvCopy=cv1-cv2;
    return *cvCopy;
}


