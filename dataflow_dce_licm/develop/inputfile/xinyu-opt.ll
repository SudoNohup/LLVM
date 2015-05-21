; ModuleID = 'inputfile/xinyu-opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

; Function Attrs: nounwind
define i32 @test7(i32 %a, i32 %b) #0 {
entry:
  %add = add nsw i32 %a, %b
  %add2 = add nsw i32 %a, %b
  %cmp = icmp slt i32 1, %a
  %cmp4 = icmp slt i32 1, %b
  br label %do.body

do.body:                                          ; preds = %do.cond3, %entry
  br label %do.body1

do.body1:                                         ; preds = %do.cond, %do.body
  br label %do.cond

do.cond:                                          ; preds = %do.body1
  br i1 %cmp, label %do.body1, label %do.end

do.end:                                           ; preds = %do.cond
  br label %do.cond3

do.cond3:                                         ; preds = %do.end
  br i1 %cmp4, label %do.body, label %do.end5

do.end5:                                          ; preds = %do.cond3
  ret i32 %add
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
