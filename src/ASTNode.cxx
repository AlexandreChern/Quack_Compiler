//
// Created by Michal Young on 9/12/18.
//
// For some Type Inference Implementations, I referenced implementations of Zayd Hammoudeh, Amie Corso, Nate Letz
// Type Inference for Classes is not done because I can't truly understand other implementations
// For Code Generation Implementations, I mainly referenced examples by Michal Young 
//

#include "ASTNode.h"
#include "semantics.h"
#include "semantics.cxx"
#include <typeinfo>

using namespace std;

namespace AST {
    // Abstract syntax tree.  ASTNode is abstract base class for all other nodes.

    int Program::init_check(set<std::string>* vars, semantics* stc) {
        for (map<std::string, AST_Type_Node>::iterator iter = stc->AST_hierarchy.begin(); iter != stc->AST_hierarchy.end(); iter++) {
            vars->insert(iter->first); 
            AST_Type_Node class_node = iter->second;
            map<std::string, class_and_methods> methods = class_node.methods;
            for(map<std::string, class_and_methods>::iterator iter = methods.begin(); iter != methods.end(); iter++) {
                vars->insert(iter->first); 
            }
        }
        if (classes_.init_check(vars) || statements_.init_check(vars)) {return 1;}
        return 0;
    }

     void Program::gen_rvalue(GenContext *ctx, string target_reg) {
            classes_.gen_rvalue(ctx, target_reg);
            GenContext class_ctx = GenContext(*ctx); 
            class_ctx.class_name = "PGM";
            class_ctx.method_name = "PGM";
            statements_.gen_rvalue(&class_ctx, target_reg);
        }

    void Method::gen_rvalue(GenContext *ctx, std::string target_reg) {
        std::string method_name = name_.get_var();
        GenContext *copy_ctx = new GenContext(*ctx);
        copy_ctx->method_name = method_name;
        AST_Type_Node class_node = ctx->stc->AST_hierarchy[copy_ctx->class_name];
        class_and_methods classandmethods = class_node.methods[method_name];
        copy_ctx->emit("");
        copy_ctx->emit("obj_" + classandmethods.return_type + " " + copy_ctx->class_name + "_method_" + method_name + "(" + copy_ctx->get_formal_argtypes(method_name) + ") {");
        statements_.gen_rvalue(copy_ctx, target_reg);
        copy_ctx->emit("}");
        copy_ctx->emit("");
    }

    std::string Method::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd) {
                formals_.type_inference(stc, v_table, mtd);
                statements_.type_inference(stc, v_table, mtd);
                return "Nothing";
            }

    

    std::string Ident::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd) {
        if (text_ == "this") {
            AST_Type_Node class_node = stc->AST_hierarchy[mtd->class_name];
            map<std::string, std::string> instance_vars = class_node.instance_vars;
            if (instance_vars.count(text_)) {return instance_vars[text_];}
            else { 
                std::cout << "Type Inference Error: Ident" << std::endl;
                return "TypeError";
            }
        }
        if (!v_table->count(text_)) { 
            cout << "Type Inference Error: Ident" << endl;
            return "TypeError"; 
        }
        else { 
            return (*v_table)[text_];
        }
    }


    void Ident::gen_rvalue(GenContext *ctx, std::string target_reg)  {
                string loc = ctx->get_local_var(text_);
                ctx->emit(target_reg + " = " + loc + ";");
            }

    std::string Dot::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd) { 
        std::string l_type = left_.type_inference(stc, v_table, mtd); 
        AST_Type_Node class_node = stc->AST_hierarchy[l_type];
        std::string r_id = right_.get_var();
        std::string l_id = left_.get_var();
        map<string, string> instance_vars = class_node.instance_vars;
        if (!instance_vars.count(r_id)) {
            std::cout << "Type Inference Error: Dot" << std::endl;
            return "TypeError";
        }
        return instance_vars[r_id];
    }    

    void Dot::gen_rvalue(GenContext *ctx, std::string target_reg)  {
            std::string var = get_var();
            std::string loc = ctx->get_local_var(var);
            ctx->emit(target_reg + " = " + loc + ";");
        }

    std::string Dot::gen_lvalue(GenContext *ctx)  {
            std::string var = get_var();
            return ctx->get_local_var(var);
        }



    std::string Program::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd) { 
        classes_.type_inference(stc, v_table, mtd);
        class_and_method* pgm_mtd = new class_and_method("PGM", "");
        map<std::string, std::string>* pgmv_table = &(stc->AST_hierarchy)["PGM"].instance_vars;
        statements_.type_inference(stc, pgmv_table, pgm_mtd);
        return "Nothing";
    }



    std::string Typecase::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd) {
        expr_.type_inference(stc, v_table, mtd);
        cases_.type_inference(stc, v_table, mtd);
        return "Nothing";
    }



    std::string Type_Alternative::type_inference(semantics* stc, map<string, string>* v_table, class_and_method* mtd) {
        ident_.type_inference(stc, v_table, mtd);
        class_name_.type_inference(stc, v_table, mtd);

        map<std::string, std::string>* local_vtable = new map<std::string, std::string>(*v_table);
        (*local_vtable)[ident_.get_var()] = class_name_.get_var();
        block_.type_inference(stc, local_vtable, mtd);
        return "Nothing";
    }

    std::string Construct::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd) { 
        actuals_.type_inference(stc, v_table, mtd);
        map<std::string, AST_Type_Node> AST_hierarchy = stc->AST_hierarchy;
        std::string method_name = method_.get_var();
        // Not Implemented
        return method_name; 
    }

     std::string Actuals::gen_lvalue(GenContext *ctx){
        vector<std::string> actual_regs = vector<string>();
        for (ASTNode *actual: elements_) {
            std::string reg = ctx->alloc_reg(ctx->get_type(*actual));
            actual_regs.push_back(reg);
            actual->gen_rvalue(ctx, reg);
        }
        std::string actuals = " ";
            for (std::string reg: actual_regs) {
                actuals = actuals + reg + ", ";
            }
            actuals = actuals.erase(actuals.length() - 2, 2); 
            return actuals;
        }

    std::string If::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd) {
        std::string cond_type = cond_.type_inference(stc, v_table, mtd);
        if (cond_type != "Boolean") {
            cout << "TypeError Inference Error: If" << endl;
        }
        truepart_.type_inference(stc, v_table, mtd);
        falsepart_.type_inference(stc, v_table, mtd);
        return "Nothing";
    }

    void  If::gen_rvalue(GenContext* ctx, std::string target_reg){
            std::string then_statement = ctx->new_branch_label("then");
            std::string else_statement = ctx->new_branch_label("else");
            std::string end_statement = ctx->new_branch_label("endif");
            cond_.gen_branch(ctx, then_statement, else_statement);
            ctx->emit(then_statement + ": ;");
            truepart_.gen_rvalue(ctx, target_reg);
            ctx->emit(std::string("goto ") + end_statement + ";");
            ctx->emit(else_statement + ": ;");
            falsepart_.gen_rvalue(ctx, target_reg);
            ctx->emit(end_statement + ": ;");
        }
    
    int If::init_check(set<std::string>* vars) {
            if (cond_.init_check(vars) || truepart_.init_check(vars) || falsepart_.init_check(vars)) {return 1;}
            // Not complete
            return 0;
        }  
    

    std::string Call::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd) {
        std::string receiver_type = receiver_.type_inference(stc, v_table, mtd);
        std::string method_name = method_.get_var();
        method_.type_inference(stc, v_table, mtd);
        actuals_.type_inference(stc, v_table, mtd);
        map<std::string, AST_Type_Node> AST_hierarchy = stc->AST_hierarchy;
        AST_Type_Node receiver_node = AST_hierarchy[receiver_type];
        map<std::string, class_and_methods> methods = receiver_node.methods;
        // Not complete
        return methods[method_name].return_type;    
    }

    void Call::gen_rvalue(GenContext *ctx, std::string target_reg) {
            std::string method_name = method_.get_var();
            std::string recv_type = ctx->get_type(receiver_);
            std::string recv_reg = ctx->alloc_reg(recv_type);
            receiver_.gen_rvalue(ctx, recv_reg);
            string actuals = actuals_.gen_lvalue(ctx);
            ctx->emit(target_reg + " = " + recv_reg + "->clazz->" + method_name + "(" + recv_reg + ", " + actuals + ");");
        }

    void Call::gen_branch(GenContext *ctx, string true_branch, string false_branch){
            std::string method_type = ctx->get_type(*this);
            std::string reg = ctx->alloc_reg(method_type);
            gen_rvalue(ctx, reg);
            ctx->emit(string("if (") + reg + ") goto " + true_branch + ";");
            ctx->emit(string("goto ") + false_branch + ";");
            ctx->free_reg(reg);
        }

    string AssignDeclare::type_inference(semantics* stc, map<string, string>* v_table, class_and_method* mtd)  {
        lexpr_.type_inference(stc, v_table, mtd);
        std::string r_type = rexpr_.type_inference(stc, v_table, mtd);
        std::string l_var = lexpr_.get_var();
        std::string static_type = static_type_.get_var();
        map<string, string> instance_vars = (stc->AST_hierarchy)[mtd->class_name].instance_vars;
        std::string l_type = (*v_table)[l_var];
        std::string lca = stc->Type_LCA(l_type, r_type);
        if (l_type != lca) { 
            if (!(stc->is_subtype(lca, static_type))) {
                (*v_table)[l_var] = "TypeError";
                cout << "Type Inference Error: AssignDeclare" << endl;
            }
            (*v_table)[l_var] = lca;
            stc->modified = 1;
        }
        return "Nothing";
    }

    int Assign::init_check(set<std::string>* vars) {
            if (rexpr_.init_check(vars) || lexpr_.init_check(vars)) { return 1; }
            vars->insert(lexpr_.get_var());
            return 0;
        }    

    std::string Assign::type_inference(semantics* stc, map<string, string>* v_table, class_and_method* mtd)  {
        lexpr_.type_inference(stc, v_table, mtd);
        std::string r_type = rexpr_.type_inference(stc, v_table, mtd);
        std::string l_var = lexpr_.get_var();
        map<std::string, std::string> instance_vars = (stc->AST_hierarchy)[mtd->class_name].instance_vars;
        std::string l_type = (*v_table)[l_var];
        std::string LCA = stc->Type_LCA(l_type, r_type);
        if (l_type != LCA) { 
            (*v_table)[l_var] = LCA;
            stc->modified = 1;
        }
        return "Nothing";
    }

    void Load::gen_rvalue(GenContext *ctx, std::string target_reg) {
            std::string var = get_var();
            std::string loc = ctx->get_local_var(var);
            ctx->emit(target_reg + " = " + loc + ";");
        }

    std::string Load::gen_lvalue(GenContext *ctx) {
            std::string var = get_var();
            return ctx->get_local_var(var);
        }

    void Assign::gen_rvalue(GenContext *ctx, std::string target_reg)  {
            std::string type = ctx->get_type(lexpr_);
            std::string reg = ctx->alloc_reg(type);
            std::string loc = lexpr_.gen_lvalue(ctx);
            rexpr_.gen_rvalue(ctx, reg);
            ctx->emit(loc + " = " + type + reg + ";");
        }

    string Methods::type_inference(semantics* stc, map<string, string>* v_table, class_and_method* mtd) {

        for (Method* method: elements_) {
            std::string method_name = method->name_.get_var();
            AST_Type_Node class_entry = stc->AST_hierarchy[mtd->class_name];
            class_and_methods classandmethods = class_entry.methods[method_name];
            map<std::string, std::string>* method_vars = classandmethods.vars;
            method->type_inference(stc, method_vars, new class_and_method(mtd->class_name, method_name));
            map<std::string, std::string> class_instance = class_entry.instance_vars;
            for(map<std::string, std::string>::iterator iter = method_vars->begin(); iter != method_vars->end(); iter++) {
                if (class_instance.count(iter->first)) { 
                    std::string method_type = iter->second;
                    std::string class_type = class_instance[iter->first];
                    if (!stc->is_subtype(method_type, class_type)) {
                        std::cout << "Type Inference Error: Methods" << std::endl;
                    }
                }
            }
        }
        return "Nothing";
    }

    string Classes::type_inference(semantics* stc, map<string, string>* v_table, class_and_method* mtd) {
        // Not implemented
        return "Nothing";
    }

    void Classes::gen_rvalue(GenContext* ctx, std::string target_reg){
            for (Class *cls: elements_) {
                std::string class_name = cls->name_.get_var();
                GenContext class_ctx = GenContext(*ctx); 
                class_ctx.class_name = class_name;
                cls->gen_rvalue(&class_ctx, target_reg);
            }
    }

   

    void Assign::get_vars(map<std::string, std::string>* v_table) {
            std::string var_name = lexpr_.get_var();
            if (var_name.rfind("this", 0) == 0) {
                (*v_table)[var_name] = "TypeError";
            }
        }

    void While::gen_rvalue(GenContext* ctx, std::string target_reg) {
            string check_statement = ctx->new_branch_label("check_cond");
            string loop_statement = ctx->new_branch_label("loop");
            string end_statement = ctx->new_branch_label("endwhile");
            ctx->emit(check_statement + ": ;");
            cond_.gen_branch(ctx, loop_statement, end_statement);
            ctx->emit(loop_statement + ": ;");
            body_.gen_rvalue(ctx, target_reg);
            ctx->emit("goto c" + check_statement + ";");
            ctx->emit(end_statement + ": ;");
        }

    int While::init_check(set<std::string>* vars){
            if (cond_.init_check(vars)) {return 1;}
            if (body_.init_check(new set<std::string>(*vars))) {return 1;}
            return 0;
        }  

    std::string  While::type_inference(semantics* stc,  map<std::string, std::string>* v_table, class_and_method* mtd){
        std::string cond_type = cond_.type_inference(stc, v_table, mtd);
        if (cond_type != "Boolean"){
            std::cout << "Type Inference Error: While" << std::endl;
        }
        body_.type_inference(stc,v_table, mtd);
        return "Nothing";
    }

    std::string And::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd){
            string left_type = left_.type_inference(stc, v_table, mtd);
            string right_type = right_.type_inference(stc, v_table, mtd);
            if (left_type != "Boolean" || right_type != "Boolean") {return "Type Inference Error: And";}
            return "Boolean";
        }

    std::string Or::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd) {
            string left_type = left_.type_inference(stc, v_table, mtd);
            string right_type = right_.type_inference(stc, v_table, mtd);
            if (left_type != "Boolean" || right_type != "Boolean") {return "Type Inference Error: Or";}
            return "Boolean";
        }

     std::string Not::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd){
            string left_type = left_.type_inference(stc, v_table, mtd);
            if (left_type != "Boolean") {return "Type Inference Error: Not";}
            return "Boolean";
        }

    std::string Class::type_inference(semantics* stc, map<std::string, std::string>* v_table, class_and_method* mtd) {
            // Not Implemented
            return "Nothing";
    }

     int Class::init_check(set<std::string>* vars) {
                if (constructor_.init_check(vars) || methods_.init_check(vars)) {return 1;}
                return 0;
            }  

    void Class::gen_rvalue(GenContext* ctx, std::string target_reg) {
                string class_name = name_.get_var();
                ctx->emit("typedef struct class_" + class_name + "_struct* " + class_name + ";");
                ctx->emit("");
                ctx->emit("typedef struct obj_" + class_name + "_struct {");
                ctx->emit("");
                ctx->emit("typedef struct obj_" + class_name + "* obj_" + class_name + ";");
                ctx->emit("");
                ctx->emit("struct class_" + class_name + "_struct;");
                ctx->emit("struct obj_" + class_name + ";");
                ctx->emit("");
                ctx->emit( class_name + " clazz;");
                ctx->emit_instance_vars();
                ctx->emit("} * obj_" + class_name + ";");
                ctx->emit("");

                ctx->emit("struct class_" + class_name + "_struct the_class_" + class_name + "_struct;");
                ctx->emit("");

                ctx->emit("struct class_" + class_name + "_struct {");
                ctx->emit("obj_" + class_name + " (*constructor) (" + ctx->get_formal_argtypes("constructor") + ");");
                ctx->method_signature(); 

                ctx->emit("};\n");
                ctx->emit("extern class_" + class_name + " the_class_" + class_name + ";");
                ctx->emit("");

                GenContext * construct_ctx = new GenContext(*ctx);
                construct_ctx->method_name = "constructor";
                constructor_.gen_rvalue(construct_ctx, target_reg);
                methods_.gen_rvalue(ctx, target_reg);
                ctx->emit_class_struct();
            }

    string Return::type_inference(semantics* stc, map<string, string>* v_table, class_and_method* mtd) {
        std::string method_name = mtd->method_name;
        AST_Type_Node class_node = stc->AST_hierarchy[mtd->class_name];
        class_and_methods class_and_methods = class_node.methods[method_name];
        std::string method_type = class_and_methods.return_type;
        std::string inference_type = expr_.type_inference(stc, v_table, mtd);
        if (!stc->is_subtype(inference_type, method_type)) {
            cout << "Type Inference Error: Return" << endl;
        }
        return "Nothing";
    }

    // JSON representation of all the concrete node types.
    // This might be particularly useful if I want to do some
    // tree manipulation in Python or another language.  We'll
    // do this by emitting into a stream.

    // --- Utility functions used by node-specific json output methods

    /* Indent to a given level */
    void ASTNode::json_indent(ostream& out, AST_print_context& ctx) {
        if (ctx.indent_ > 0) {
            out << endl;
        }
        for (int i=0; i < ctx.indent_; i++) {
            out << "    ";
        }
    }

    /* The head element looks like { "kind" : "block", */
    void ASTNode::json_head(string node_kind, ostream& out, AST_print_context& ctx) {
        json_indent(out, ctx);
        out << "{ \"kind\" : \"" << node_kind << "\"," ;
        ctx.indent(); 
        return;
    }

    void ASTNode::json_close(ostream& out, AST_print_context& ctx) {
        out << "}";
        ctx.dedent();
    }

    void ASTNode::json_child(string field, ASTNode& child, ostream& out, AST_print_context& ctx, char sep) {
        json_indent(out, ctx);
        out << "\"" << field << "\" : ";
        child.json(out, ctx);
        out << sep;
    }

    void Stub::json(ostream& out, AST_print_context& ctx) {
        json_head("Stub", out, ctx);
        json_indent(out, ctx);
        out  << "\"rule\": \"" <<  name_ << "\"";
        json_close(out, ctx);
    }


    void Program::json(ostream &out, AST::AST_print_context &ctx) {
        json_head("Program", out, ctx);
        json_child("classes_", classes_, out, ctx);
        json_child("statements_", statements_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Formal::json(ostream &out, AST::AST_print_context &ctx) {
        json_head("Formal", out, ctx);
        json_child("var_", var_, out, ctx);
        json_child("type_", type_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Method::json(ostream &out, AST::AST_print_context &ctx) {
        json_head("Method", out, ctx);
        json_child("name_", name_, out, ctx);
        json_child("formals_", formals_, out, ctx);
        json_child("returns_", returns_, out, ctx);
        json_child("statements_", statements_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Assign::json(ostream& out, AST_print_context& ctx) {
        json_head("Assign", out, ctx);
        json_child("lexpr_", lexpr_, out, ctx);
        json_child("rexpr_", rexpr_, out, ctx, ' ');
        json_close(out, ctx);
     }

    void AssignDeclare::json(ostream& out, AST_print_context& ctx) {
        json_head("Assign", out, ctx);
        json_child("lexpr_", lexpr_, out, ctx);
        json_child("rexpr_", rexpr_, out, ctx);
        json_child("static_type_", static_type_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Return::json(ostream &out, AST::AST_print_context &ctx) {
        json_head("Return", out, ctx);
        json_child("expr_", expr_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void If::json(ostream& out, AST_print_context& ctx) {
        json_head("If", out, ctx);
        json_child("cond_", cond_, out, ctx);
        json_child("truepart_", truepart_, out, ctx);
        json_child("falsepart_", falsepart_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void While::json(ostream& out, AST_print_context& ctx) {
        json_head("While", out, ctx);
        json_child("cond_", cond_, out, ctx);
        json_child("body_", body_, out, ctx, ' ');
        json_close(out, ctx);
    }


    void Typecase::json(ostream& out, AST_print_context& ctx) {
        json_head("Typecase", out, ctx);
        json_child("expr_", expr_, out, ctx);
        json_child("cases_", cases_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Type_Alternative::json(ostream& out, AST_print_context& ctx) {
        json_head("Type_Alternative", out, ctx);
        json_child("ident_", ident_, out, ctx);
        json_child("class_name_", class_name_, out, ctx);
        json_child("block_", block_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Load::json(ostream &out, AST::AST_print_context &ctx) {
        json_head("Load", out, ctx);
        json_child("loc_", loc_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Ident::json(ostream& out, AST_print_context& ctx) {
        json_head("Ident", out, ctx);
        out << "\"text_\" : \"" << text_ << "\"";
        json_close(out, ctx);
    }

    void Class::json(ostream &out, AST::AST_print_context &ctx) {
        json_head("Class", out, ctx);
        json_child("name_", name_, out, ctx);
        json_child("super_", super_, out, ctx);
        json_child("constructor_", constructor_, out, ctx);
        json_child("methods_", methods_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Call::json(ostream &out, AST::AST_print_context &ctx) {
        json_head("Call", out, ctx);
        json_child("obj_", receiver_, out, ctx);
        json_child("method_", method_, out, ctx);
        json_child("actuals_", actuals_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Construct::json(ostream &out, AST::AST_print_context &ctx) {
        json_head("Construct", out, ctx);
        json_child("method_", method_, out, ctx);
        json_child("actuals_", actuals_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void IntConst::json(ostream& out, AST_print_context& ctx) {
        json_head("IntConst", out, ctx);
        out << "\"value_\" : " << value_ ;
        json_close(out, ctx);
    }

    void StrConst::json(ostream& out, AST_print_context& ctx) {
        json_head("StrConst", out, ctx);
        out << "\"value_\" : \"" << value_  << "\"";
        json_close(out, ctx);
    }


    void BinOp::json(ostream& out, AST_print_context& ctx) {
        json_head(opsym, out, ctx);
        json_child("left_", left_, out, ctx);
        json_child("right_", right_, out, ctx, ' ');
        json_close(out, ctx);
    }


    void Not::json(ostream& out, AST_print_context& ctx) {
        json_head("Not", out, ctx);
        json_child("left_", left_, out, ctx, ' ');
        json_close(out, ctx);
    }

    void Dot::json(ostream& out, AST_print_context& ctx) {
        json_head("Dot", out, ctx);
        json_child("left_", left_, out, ctx);
        json_child("right_", right_, out, ctx, ' ');
        json_close(out, ctx);
    }


    /* Convenience factory for operations like +, -, *, / */
    Call* Call::binop(string opname, Expr& receiver, Expr& arg) {
        Ident* method = new Ident(opname);
        Actuals* actuals = new Actuals();
        actuals->append(&arg);
        return new Call(receiver, *method, *actuals);
    }
}