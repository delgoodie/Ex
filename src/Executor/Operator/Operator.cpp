#include "Operator.h"

namespace Executor {
    namespace Operator
    {
        namespace Conversion
        {
            Expr NumberToString(const Expr& expr)
            {
                //std::string string = std::to_string(expr.number);
                //return Expr(StringLink::StringToStringLinkHeap(string), string.size());
                return expr;
            }
            Expr StringToNumber(const Expr& expr)
            {
                //std::string string = StringLink::StringLinkToString(expr.string.head);
                //return Expr(std::stod(string));
                return expr;
            }
            Expr NumberToBool(const Expr& expr)
            {
                return Expr(expr.number != 0);
            }
            Expr BoolToNumber(const Expr& expr)
            {
                return Expr(expr.boolean ? 1.0 : 0.0);
            }
            Expr StringToBool(const Expr& expr)
            {
                ex_boolean_t value = true;
                if (expr.string.length == 0)
                    value = false;
                else if (expr.string.length == 5 && strcmp(expr.string.head->string, "false") == 0)
                    value = false;
                else if (expr.string.length == 1 && strcmp(expr.string.head->string, "0") == 0)
                    value = false;

                return Expr(value);
            }
            Expr BooleanToString(const Expr& expr)
            {
                //std::string string = (expr.boolean ? "true" : "false");
                //return Expr(StringLink::StringToStringLinkHeap(string), string.size());
                return expr;
            }
            Expr ObjectToBoolean(const Expr& expr)
            {
                //TODO: check if empty maybe?
                return Expr(true);
            }
            Expr ObjectToString(const Expr& expr)
            {
                //std::string string = "{}";
                //return Expr(StringLink::StringToStringLinkHeap(string), string.size());
                return expr;
            }
            Expr Convert(const Expr& expr, Expr::Type type)
            {
                if (expr.type == type)
                    return expr;

                switch (expr.type)
                {
                case Expr::Type::EX_BOOLEAN:
                    switch (type)
                    {
                    case Expr::Type::EX_NUMBER:
                        return BoolToNumber(expr);
                    case Expr::Type::EX_STRING:
                        return BooleanToString(expr);
                    default:
                        std::printf("Can't convert boolean to type %d\n", (int)type);
                        return Expr(nullptr);
                    }
                case Expr::Type::EX_NUMBER:
                    switch (type)
                    {
                    case Expr::Type::EX_BOOLEAN:
                        return NumberToBool(expr);
                    case Expr::Type::EX_STRING:
                        return NumberToString(expr);
                    default:
                        std::printf("Can't convert number to type %d\n", (int)type);
                        return Expr(nullptr);
                    }
                case Expr::Type::EX_STRING:
                    switch (type)
                    {
                    case Expr::Type::EX_BOOLEAN:
                        return StringToBool(expr);
                    case Expr::Type::EX_NUMBER:
                        return StringToNumber(expr);
                    default:
                        std::printf("Can't convert string to type %d\n", (int)type);
                        return Expr(nullptr);
                    }
                case Expr::Type::EX_OBJECT:
                    switch (type)
                    {
                    case Expr::Type::EX_BOOLEAN:
                        return ObjectToBoolean(expr);
                    case Expr::Type::EX_STRING:
                        return ObjectToString(expr);
                    default:
                        std::printf("Can't convert Object to type %d\n", (int)type);
                        return Expr(nullptr);
                    }
                default:
                    std::printf("Unconvertable Type %d\n", (int)expr.type);
                    return Expr(nullptr);
                }
            }
        }

        namespace Object
        {
            Result Access_l_r(const Expr& lhs, const Expr& rhs, Context* context) // TODO: Access l & r
            {
                return Expr(nullptr);
            }
            Result Access_r(const Expr& lhs, const Expr& rhs, Context* context) // TODO: Access r
            {
                return Expr(nullptr);
            }
            Result Access(const Expr& lhs, const Expr& rhs, Context* context) // TODO: Access
            {
                return Expr(nullptr);
            }
            Result Assign(const Expr& lhs, const Expr& rhs, Context* context) // TODO: Assign
            {
                return Expr(nullptr);
            }
        }

        namespace Control
        {
            Result If(const Expr& lhs, const Expr& rhs, Context* context) // TODO: If
            {
                return Expr(nullptr);
            }
            Result While(const Expr& lhs, const Expr& rhs, Context* context) // TODO: While
            {
                return Expr(nullptr);
            }
            Result Else(const Expr& lhs, const Expr& rhs, Context* context) // TODO: Else
            {
                return Expr(nullptr);
            }
            Result Return(const Expr& lhs, const Expr& rhs, Context* context) // TODO: Return
            {
                return Expr(nullptr);
            }
            Result Comma_l_r(const Expr& lhs, const Expr& rhs, Context* context)
            {
                return rhs;
            }
            Result Comma_l(const Expr& lhs, const Expr& rhs, Context* context)
            {
                return lhs;
            }
        }

        namespace Literal
        {
            Result False(const Expr& lhs, const Expr& rhs, Context* context)
            {
                return Result(Expr(false));
            }
            Result Eval_l_r(const Expr& lhs, const Expr& rhs, Context* context)
            {
                return Expr(nullptr);
            }
            Result Eval_r(const Expr& lhs, const Expr& rhs, Context* context)
            {
                return Expr(nullptr);
            }
            Result SizeOf(const Expr& lhs, const Expr& rhs, Context* context) // TODO: SizeOf
            {
                return Expr(nullptr);
            }
            Result Add_r(const Expr& lhs, const Expr& rhs, Context* context) // TODO: Add property / abs
            {
                return Expr(nullptr);
            }
            Result Subtract_r(const Expr& lhs, const Expr& rhs, Context* context) // TODO: Delete property / negate
            {
                return Expr(nullptr);
            }
            Result Exponent(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                return Result(Expr(pow(c_lhs.number, c_rhs.number)));
            }
            Result Modulus(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                return Result(Expr((ex_number_t)((int)c_lhs.number % (int)c_rhs.number)));
            }
            Result Multiply(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                return Result(Expr(c_lhs.number * c_rhs.number));
            }
            Result Divide(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                // TODO: divide by zero error
                return Result(Expr(c_lhs.number / c_rhs.number));
            }
            Result Add_l_r(const Expr& lhs, const Expr& rhs, Context* context)
            {
                // String Concat
                if (lhs.type == Expr::Type::EX_STRING || rhs.type == Expr::Type::EX_STRING)
                {
                    Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_STRING);
                    Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_STRING);
                    // TODO: add string to SHeap (needs context)
                    return c_lhs;
                }
                else if (lhs.type == Expr::Type::EX_NUMBER || rhs.type == Expr::Type::EX_NUMBER) // Numerical Addition
                {
                    Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                    Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                    return Result(Expr(c_lhs.number + c_rhs.number));
                }
                else if (lhs.type == Expr::Type::EX_BOOLEAN && rhs.type == Expr::Type::EX_BOOLEAN)
                {
                    return Result(Expr(lhs.boolean || rhs.boolean));
                }
                else
                {
                    // unsuported value
                    return Result(Expr(nullptr));
                }
            }
            Result Subtract_l_r(const Expr& lhs, const Expr& rhs, Context* context)
            {
                //TODO: remove property from object
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                return Result(Expr(c_lhs.number - c_rhs.number));
            }
        }

        namespace Logic
        {
            Result LessThan(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                return Result(Expr(c_lhs.number < c_rhs.number));
            }
            Result GreaterThan(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                return Result(Expr(c_lhs.number > c_rhs.number));
            }
            Result LessThanOrEqualTo(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                return Result(Expr(c_lhs.number <= c_rhs.number));
            }
            Result GreaterThanOrEqualTo(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                return Result(Expr(c_lhs.number >= c_rhs.number));
            }
            Result Not(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_BOOLEAN);
                return Result(Expr(!c_rhs.boolean));
            }
            Result And(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_BOOLEAN);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_BOOLEAN);
                return Result(Expr(c_lhs.boolean && c_rhs.boolean));
            }
            Result Or(const Expr& lhs, const Expr& rhs, Context* context)
            {
                Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_BOOLEAN);
                Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_BOOLEAN);
                return Result(Expr(c_lhs.boolean || c_rhs.boolean));
            }
            Result EqualTo(const Expr& lhs, const Expr& rhs, Context* context)
            {
                ex_boolean_t value = false;
                if (lhs.type == Expr::Type::EX_STRING || rhs.type == Expr::Type::EX_STRING) // String Comparison
                {
                    Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_STRING);
                    Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_STRING);
                    // TODO: StringLink cmp
                    value = false;
                }
                else if (lhs.type == Expr::Type::EX_NUMBER || rhs.type == Expr::Type::EX_NUMBER) // Number comparison
                {
                    Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                    Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                    value = c_lhs.number == c_rhs.number; // TODO: rounding support? 0 == 1e-9
                }
                else if (lhs.type == Expr::Type::EX_BOOLEAN || rhs.type == Expr::Type::EX_BOOLEAN) // Boolean Comparison
                {
                    Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_BOOLEAN);
                    Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_BOOLEAN);
                    value = c_lhs.boolean == c_rhs.boolean;
                }
                else if (lhs.type == Expr::Type::EX_OBJECT && rhs.type == Expr::Type::EX_OBJECT) // Object Comparison
                {
                    //TODO: Object comparison
                    value = false;
                }
                else
                {
                    //TODO: handle other cases
                    value = false;
                }
                return Result(Expr(value));
            }
            Result NotEqualTo(const Expr& lhs, const Expr& rhs, Context* context)
            {
                ex_boolean_t value = false;
                if (lhs.type == Expr::Type::EX_STRING || rhs.type == Expr::Type::EX_STRING) // String Comparison
                {
                    Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_STRING);
                    Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_STRING);
                    // TODO: StringLink cmp
                    value = false;
                }
                else if (lhs.type == Expr::Type::EX_NUMBER || rhs.type == Expr::Type::EX_NUMBER) // Number comparison
                {
                    Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_NUMBER);
                    Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_NUMBER);
                    value = c_lhs.number != c_rhs.number; // TODO: rounding support? 0 == 1e-9
                }
                else if (lhs.type == Expr::Type::EX_BOOLEAN || rhs.type == Expr::Type::EX_BOOLEAN) // Boolean Comparison
                {
                    Expr c_lhs = Conversion::Convert(lhs, Expr::Type::EX_BOOLEAN);
                    Expr c_rhs = Conversion::Convert(rhs, Expr::Type::EX_BOOLEAN);
                    value = c_lhs.boolean != c_rhs.boolean;
                }
                else if (lhs.type == Expr::Type::EX_OBJECT && rhs.type == Expr::Type::EX_OBJECT) // Object Comparison
                {
                    //TODO: Object comparison
                    value = false;
                }
                else
                {
                    //TODO: handle other cases
                    value = false;
                }
                return Result(Expr(value));
            }
        }
    }
}