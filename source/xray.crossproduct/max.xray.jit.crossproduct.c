/* 
	xray.jit.crossproduct
	Wesley Smith
	wesley.hoke@gmail.com
	
	last modified: 12-7-2006
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_xray_jit_crossproduct 
{
	t_object			ob;
	void				*obex;
} t_max_xray_jit_crossproduct;

t_jit_err xray_jit_crossproduct_init(void); 

void *max_xray_jit_crossproduct_new(t_symbol *s, long argc, t_atom *argv);
void max_xray_jit_crossproduct_free(t_max_xray_jit_crossproduct *x);
void max_xray_jit_crossproduct_assist(t_max_xray_jit_crossproduct *x, void *b, long m, long a, char *s);
void max_xray_jit_crossproduct_bang(t_max_xray_jit_crossproduct *x);
void max_xray_jit_crossproduct_mproc(t_max_xray_jit_crossproduct *x, void *mop);
void *max_xray_jit_crossproduct_class;

void main(void)
{	
	void *p,*q;
	
	xray_jit_crossproduct_init();	
	setup(&max_xray_jit_crossproduct_class, max_xray_jit_crossproduct_new, (method)max_xray_jit_crossproduct_free, (short)sizeof(t_max_xray_jit_crossproduct), 
		0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_xray_jit_crossproduct,obex));
	q = jit_class_findbyname(gensym("xray_jit_crossproduct"));    
    max_jit_classex_mop_wrap(p,q,0);
    max_jit_classex_standard_wrap(p,q,0); 	
 	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);
}



void max_xray_jit_crossproduct_free(t_max_xray_jit_crossproduct *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_xray_jit_crossproduct_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_xray_jit_crossproduct *x;
	void *o;

	if (x=(t_max_xray_jit_crossproduct *)max_jit_obex_new(max_xray_jit_crossproduct_class,gensym("xray_jit_crossproduct"))) {
		if (o=jit_object_new(gensym("xray_jit_crossproduct"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			max_jit_attr_args(x,argc,argv);
		} else {
			error("xray.jit.crossproduct: could not allocate object");
			freeobject(x);
		}
	}
	return (x);
}

