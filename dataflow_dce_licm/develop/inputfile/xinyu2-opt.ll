; ModuleID = 'inputfile/xinyu2-opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [12 x i8] c"%f seconds\0A\00", align 1

; Function Attrs: nounwind
define i32 @test1(i32 %a, i32 %b) #0 {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc31, %entry
  %count1.0 = phi i64 [ 1, %entry ], [ %inc27, %for.inc31 ]
  %count.0 = phi i64 [ 1, %entry ], [ %count.4, %for.inc31 ]
  %i.0 = phi i32 [ 0, %entry ], [ %inc32, %for.inc31 ]
  %cmp = icmp slt i32 %i.0, 30
  br i1 %cmp, label %for.body, label %for.end33

for.body:                                         ; preds = %for.cond
  br label %do.body

do.body:                                          ; preds = %do.cond28, %for.body
  %count1.1 = phi i64 [ %count1.0, %for.body ], [ %inc27, %do.cond28 ]
  %count.1 = phi i64 [ %count.0, %for.body ], [ %count.4, %do.cond28 ]
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc, %do.body
  %count.2 = phi i64 [ %count.1, %do.body ], [ %inc, %for.inc ]
  %j.0 = phi i32 [ 0, %do.body ], [ %inc26, %for.inc ]
  %cmp2 = icmp slt i32 %j.0, 30
  br i1 %cmp2, label %for.body3, label %for.end

for.body3:                                        ; preds = %for.cond1
  %add23 = add nsw i32 %a, %b
  br label %do.body4

do.body4:                                         ; preds = %do.cond, %for.body3
  %count.3 = phi i64 [ %count.2, %for.body3 ], [ %inc, %do.cond ]
  %inc = add nsw i64 %count.3, 1
  br label %do.cond

do.cond:                                          ; preds = %do.body4
  %cmp24 = icmp slt i64 %inc, 300000000
  br i1 %cmp24, label %do.body4, label %do.end

do.end:                                           ; preds = %do.cond
  %cmp25 = icmp sgt i32 %add23, 10
  br i1 %cmp25, label %if.then, label %if.end

if.then:                                          ; preds = %do.end
  br label %for.end

if.end:                                           ; preds = %do.end
  br label %for.inc

for.inc:                                          ; preds = %if.end
  %inc26 = add nsw i32 %j.0, 1
  br label %for.cond1

for.end:                                          ; preds = %if.then, %for.cond1
  %count.4 = phi i64 [ %inc, %if.then ], [ %count.2, %for.cond1 ]
  %inc27 = add nsw i64 %count1.1, 1
  br label %do.cond28

do.cond28:                                        ; preds = %for.end
  %cmp29 = icmp slt i64 %inc27, 30000
  br i1 %cmp29, label %do.body, label %do.end30

do.end30:                                         ; preds = %do.cond28
  br label %for.inc31

for.inc31:                                        ; preds = %do.end30
  %inc32 = add nsw i32 %i.0, 1
  br label %for.cond

for.end33:                                        ; preds = %for.cond
  ret i32 %a
}

; Function Attrs: nounwind
define i32 @main() #0 {
entry:
  %call = call i32 @clock() #2
  %call1 = call i32 @test1(i32 1, i32 2)
  %call2 = call i32 @clock() #2
  %sub = sub nsw i32 %call2, %call
  %conv = sitofp i32 %sub to double
  %div = fdiv double %conv, 1.000000e+06
  %call3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([12 x i8]* @.str, i32 0, i32 0), double %div)
  ret i32 0
}

; Function Attrs: nounwind
declare i32 @clock() #0

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
