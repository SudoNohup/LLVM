; ModuleID = 'strength-simp.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: nounwind readnone
define i32 @compute(i32 %a, i32 %b) #0 {
entry:
  %add4 = mul i32 %a, 13
  %div.neg = sdiv i32 %b, -2
  %sub = add i32 %div.neg, %add4
  %div5.neg = sdiv i32 %b, -4
  %sub6 = add i32 %sub, %div5.neg
  %div7.neg = sdiv i32 %b, -8
  %sub8 = add i32 %sub6, %div7.neg
  ret i32 %sub8
}

; Function Attrs: nounwind
define i32 @main() #1 {
entry:
  %call = tail call i32 @compute(i32 1, i32 8)
  %call1 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %call) #2
  ret i32 0
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) #1

attributes #0 = { nounwind readnone "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
